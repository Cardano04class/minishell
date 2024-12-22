/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_and_red_token_parsing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:52:01 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/22 15:40:04 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_filename(void)
{
	char	*file_name;
	char	line[2];
	int		fd;
	int		c;

	file_name = _malloc(sizeof(char) * 12, 'm');
	if (file_name == NULL)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	c = 0;
	while (c < 11)
	{
		read(fd, line, 1);
		if (ft_isalpha(line[0]))
			file_name[c++] = line[0];
	}
	file_name[c] = '\0';
	close(fd);
	return (file_name);
}

void	create_heredoc_file(t_list *lst, t_cmd *command)
{
	char	*name;

	name = heredoc_filename();
	name = ft_strjoin("/tmp/", name);
	ft_file_addback(ft_file_new(name, lst->prev->type, ft_strdup(lst->content)),
		command);
}

void	create_in_out_file(t_list *lst, t_cmd *command)
{
	ft_file_addback(ft_file_new(ft_strdup(lst->content), lst->prev->type, NULL),
		command);
}

void	process_command_arguments(t_list *lst, t_parser *vars)
{
	if (lst->content != NULL)
	{
		vars->tmp_cmd->cmd[vars->counter] = ft_strdup(lst->content);
		vars->counter++;
	}
	else
	{
		vars->tmp_cmd->cmd[vars->counter] = NULL;
		vars->counter++;
	}
}

void	handle_word_token(t_parser *vars, t_list *lst)
{
	if (vars->state == STATE_REDIRECTION)
	{
		if (lst->prev->type == HEREDOC)
			create_heredoc_file(lst, vars->tmp_cmd);
		else
			create_in_out_file(lst, vars->tmp_cmd);
		vars->state = STATE_DEFAULT;
	}
	else
		process_command_arguments(lst, vars);
}
