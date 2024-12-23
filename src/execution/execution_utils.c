/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:35:21 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/21 11:11:47 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_redirections(t_file *file, t_cmd *command)
{
	int	fd;

	while (file)
	{
		if (command->cmd[0] != NULL)
			check_if_redirection_file_valid(file);
		if (file->type == INRED || file->type == HEREDOC)
			fd = open(file->filename, O_RDONLY | O_CREAT, 0644);
		else if (file->type == OUTRED)
			fd = open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else if (file->type == APPEND)
			fd = open(file->filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (perror(""), false);
		if (file->type == INRED || file->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		file = file->next;
	}
	return (true);
}

int	is_builtins(t_cmd *command)
{
	if (command->cmd[0] != NULL)
	{
		if (ft_strcmp("echo", command->cmd[0]) == 0)
			return (1);
		else if (ft_strcmp("export", command->cmd[0]) == 0)
			return (1);
		else if (ft_strcmp("exit", command->cmd[0]) == 0)
			return (1);
		else if (ft_strcmp("cd", command->cmd[0]) == 0)
			return (1);
		else if (ft_strcmp("pwd", command->cmd[0]) == 0)
			return (1);
		else if (ft_strcmp("env", command->cmd[0]) == 0)
			return (1);
		else if (ft_strcmp("unset", command->cmd[0]) == 0)
			return (1);
	}
	return (0);
}

void	if_executable(char *str)
{
	if (access(str, X_OK) != 0)
	{
		write(2, str, ft_strlen(str));
		write(2, ": Permission denied\n", 20);
		_malloc(0, 'f');
		g_mini.exit_status = 126;
		exit(g_mini.exit_status);
	}
}

void	check_if_redirection_file_valid(t_file *file)
{
	struct stat	path_stat;

	if (file->filename[0] == '\0')
	{
		write(2, file->filename, ft_strlen(file->filename));
		write(2, ": No such file or directory\n", 28);
		g_mini.exit_status = 1;
		_malloc(0, 'f');
		exit(g_mini.exit_status);
	}
	if (stat(file->filename, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		write(2, file->filename, ft_strlen(file->filename));
		write(2, ": Is a directory\n", 17);
		g_mini.exit_status = 1;
		_malloc(0, 'f');
		exit(g_mini.exit_status);
	}
}

void	check_if_cmd_valid(t_cmd *command)
{
	struct stat	path_stat;

	if (command->cmd[0][0] == '.' && command->cmd[0][1] == '\0')
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": filename argument required\n", 29);
		_malloc(0, 'f');
		g_mini.exit_status = 2;
		exit(g_mini.exit_status);
	}
	if (stat(command->cmd[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": Is a directory\n", 17);
		_malloc(0, 'f');
		g_mini.exit_status = 126;
		exit(g_mini.exit_status);
	}
}
