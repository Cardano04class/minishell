/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:51:02 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 21:46:29 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_line_fd(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	heredoc_prompt(t_cmd *command, int fd)
{
	char	*line;

	while (1)
	{
		signal_handler(IN_HEREDOC);
		line = readline(">");
		if (line == NULL)
		{
			printf("warning : delimited by end-of-file (wanted `%s')\n",
				command->files->delimiter);
			break ;
		}
		if (!ft_strcmp(command->files->delimiter, line))
			break ;
		if (ft_strchr(line, '$') != NULL)
		{
			line = expand_in_heredoc(line);
			write_line_fd(line, fd);
		}
		else
			write_line_fd(line, fd);
	}
	return (fd);
}

void	run_heredoc(t_cmd *command)
{
	int		fd;
	int		status;
	pid_t	child_pid;

	fd = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		while (command->files != NULL)
		{
			if (command->files->type == HEREDOC)
			{
				fd = open(command->files->filename, O_WRONLY | O_CREAT, 0777);
				if (fd == -1)
					(_malloc(0, 'f'), exit(1));
				heredoc_prompt(command, fd);
			}
			command->files = command->files->next;
		}
		close(fd);
		_malloc(0, 'f');
		exit(0);
	}
	waitpid(child_pid, &status, 0);
	g_mini.exit_status = capture_exit_status(status);
}
