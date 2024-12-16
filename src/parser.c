/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/16 16:20:10 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_argument_size(t_list *lst)
{
	int count = 0;
	
	while (lst != NULL && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND || lst->type == HEREDOC)
			count--;
		lst = lst->next;
	}
	return (count);
}
// void	handle_pipe_token(t_list **lst, t_cmd	**tmp_cmd, int	*cmd_arg_size, int *index_count)
// {
// 	ft_cmd_addback(tmp_cmd, ft_cmd_new(NULL));
// 	*tmp_cmd = (*tmp_cmd)->next;
// 	*lst = (*lst)->next;
// 	cmd_arg_size = cmd_argument_size(*lst);
// 	*lst = (*lst)->prev;
// 	index_count = 0;
// 	(*tmp_cmd)->cmd = _malloc(sizeof(char *) * (*cmd_arg_size + 1), 'm');
// 	(*tmp_cmd)->cmd[*cmd_arg_size] = NULL;
// }

void	parser(t_list *lst)
{
	int		cmd_arg_size;
	int		index_count;
	t_state	state;
	t_cmd	*tmp_cmd;

	index_count = 0;
	state = STATE_DEFAULT;
	cmd_arg_size = cmd_argument_size(lst);
	
	g_mini.command->cmd = _malloc(sizeof(char *) * (cmd_arg_size + 1), 'm');
	g_mini.command->cmd[cmd_arg_size] = NULL;
	tmp_cmd = g_mini.command;
	while (lst != NULL)
	{
		if (lst->type == WORD && index_count <= cmd_arg_size)
		{
			if (state == STATE_REDIRECTION)
			{
				if (lst->prev->type == HEREDOC)
				{
					char *name = heredoc_filename();
					name = ft_strjoin("/tmp/", name);
					ft_file_addback(ft_file_new(name, lst->prev->type, ft_strdup(lst->content)));
				}
				else
					ft_file_addback(ft_file_new(ft_strdup(lst->content), lst->prev->type, NULL));
				state = STATE_DEFAULT;
			}
			else if (lst->content != NULL && lst->content[0] != '\0')
			{
				tmp_cmd->cmd[index_count] = ft_strdup(lst->content);
				index_count++;
			}
		}
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND || lst->type == HEREDOC)
			state = STATE_REDIRECTION;
		else if (lst->type == PIPE)
		{
			//handle_pipe_token(&lst, &tmp_cmd, &cmd_arg_size, &index_count);
			ft_cmd_addback(&tmp_cmd, ft_cmd_new(NULL));
			tmp_cmd = tmp_cmd->next;
			lst = lst->next;
			cmd_arg_size = cmd_argument_size(lst);
			lst = lst->prev;
			index_count = 0;
			tmp_cmd->cmd = _malloc(sizeof(char *) * (cmd_arg_size + 1), 'm');
			tmp_cmd->cmd[cmd_arg_size] = NULL;
		}
		if (lst != NULL)
			lst = lst->next;
	}
}
