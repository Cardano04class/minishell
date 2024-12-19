/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/19 02:11:47 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intialise_vars(t_parser *vars, t_list *lst)
{
	vars->counter = 0;
	vars->state = STATE_DEFAULT;
	vars->cmd_arg_size = cmd_argument_size(lst);
	g_mini.command->cmd = _malloc(sizeof(char *) * (vars->cmd_arg_size + 1),
			'm');
	g_mini.command->cmd[vars->cmd_arg_size] = NULL;
	vars->tmp_cmd = g_mini.command;
}

void	parser(t_list *lst)
{
	t_parser	vars;

	intialise_vars(&vars, lst);
	while (lst != NULL)
	{
		if (lst->type == WORD)
			handle_word_token(&vars, lst);
		else if (lst->type == INRED || lst->type == OUTRED
			|| lst->type == APPEND || lst->type == HEREDOC)
			vars.state = STATE_REDIRECTION;
		else if (lst->type == PIPE)
			create_next_command_tokens(&vars, lst);
		if (lst != NULL)
			lst = lst->next;
	}
}
