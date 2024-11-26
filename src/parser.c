/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/11/26 21:53:48 by mobouifr         ###   ########.fr       */
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

void	parser(t_list *lst)
{
	int			cmd_arg_size;
	int 		index_count;
	t_state		state;
	t_cmd		*tmp_cmd;
	
	index_count = 0;
	state = STATE_DEFAULT;
	cmd_arg_size = cmd_argument_size(lst);
	g_mini.command->cmd = malloc(sizeof(char *) * (cmd_arg_size + 1));
	g_mini.command->cmd[cmd_arg_size] = NULL;
	tmp_cmd = g_mini.command;
	while (lst != NULL)
	{
		if (lst->type == WORD && index_count <= cmd_arg_size)
		{
			if (state == STATE_HEREDOC)
			{
				ft_heredoc_addback(ft_heredoc_new(ft_strdup(lst->content)));
				state = STATE_DEFAULT;
			}
			else if (state == STATE_REDIRECTION)
			{
				ft_file_addback(ft_file_new(ft_strdup(lst->content), lst->prev->type));
				state = STATE_DEFAULT;
			}
			else
			{
				tmp_cmd->cmd[index_count] = ft_strdup(lst->content);
				index_count++;
			}
		}
		else if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND)
			state = STATE_REDIRECTION;
		else if (lst->type == HEREDOC)
			state = STATE_HEREDOC;
		else if (lst->type == PIPE)
		{
			ft_cmd_addback(&tmp_cmd, ft_cmd_new(NULL));
			tmp_cmd = tmp_cmd->next;
			lst = lst->next;
			cmd_arg_size = cmd_argument_size(lst);
			lst = lst->prev;
			index_count = 0;
			tmp_cmd->cmd = malloc(sizeof(char *) * (cmd_arg_size + 1));
			tmp_cmd->cmd[cmd_arg_size] = NULL;
		}
		if (lst != NULL)
			lst = lst->next;
	}
}




























// 	while (lst != NULL)
// 	{
// 		if (lst->type == WORD)
// 		{	
// 			if (flag == 1)
// 			{
// 				str = ft_ssplit(lst->content);
// 				free(lst->content);
// 				lst->content = str[0];
// 				remove_first_element(str);
// 				g_mini.command->cmd = str;
// 			}
// 			else
// 				g_mini.command->cmd = ft_ssplit(lst->content);
				
// 			j = 0;
// 			while (g_mini.command->cmd[j] != NULL)
// 			{
// 				printf("%s\n", g_mini.command->cmd[j]);
// 				j++;
// 			}
// 		}
// 		else if (lst->type == INRED)
// 		{
// 			ft_file_addback(ft_file_new(ft_strdup(lst->next->content), INRED));
// 			flag = 1;		
// 		}
// 		else if (lst->type == OUTRED)
// 		{
// 			ft_file_addback(ft_file_new(ft_strdup(lst->next->content), OUTRED));
// 			flag = 1;		
// 		}
// 		else if (lst->type == APPEND)
// 		{
// 			ft_file_addback(ft_file_new(ft_strdup(lst->next->content), APPEND));			
// 			flag = 1;
// 		}
// 		else if (lst->type == HEREDOC)
// 		{	
// 		}
// 		else if (lst->type == PIPE)
// 		{	
// 			ft_cmd_addback(&g_mini.command, ft_cmd_new(NULL));
// 			g_mini.command= g_mini.command->next;
// 		}
// 		lst = lst->next;
// 	}
// }
