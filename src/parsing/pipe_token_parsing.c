/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:53:30 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:09:39 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_argument_size(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		else if (lst->type == INRED || lst->type == OUTRED
			|| lst->type == APPEND || lst->type == HEREDOC)
			count--;
		lst = lst->next;
	}
	return (count);
}

void	create_next_command_tokens(t_parser *vars, t_list *lst)
{
	ft_cmd_addback(&vars->tmp_cmd, ft_cmd_new(NULL));
	vars->tmp_cmd = vars->tmp_cmd->next;
	lst = lst->next;
	vars->cmd_arg_size = cmd_argument_size(lst);
	lst = lst->prev;
	vars->counter = 0;
	vars->tmp_cmd->cmd = _malloc(sizeof(char *) * (vars->cmd_arg_size + 1),
			'm');
	vars->tmp_cmd->cmd[vars->cmd_arg_size] = NULL;
}
