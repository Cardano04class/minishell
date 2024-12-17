/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/17 23:49:10 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_parser
{
	int		cmd_arg_size;
	int		counter;
	t_state	state;
	t_cmd	*tmp_cmd;
}			t_parser;

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
void	create_heredoc_file(t_list *lst)
{
	char	*name;

	name = heredoc_filename();
	name = ft_strjoin("/tmp/", name);
	ft_file_addback(ft_file_new(name, lst->prev->type,
			ft_strdup(lst->content)));
}

void	create_in_out_file(t_list *lst)
{
	ft_file_addback(ft_file_new(ft_strdup(lst->content), lst->prev->type,
			NULL));
}

void	add_command_argument(t_list *lst, t_parser *vars)
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
			create_heredoc_file(lst);
		else
			create_in_out_file(lst);
		vars->state = STATE_DEFAULT;
	}
	else
		add_command_argument(lst, vars);
}
void	create_next_command_token(t_parser *vars, t_list *lst)
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
void	intialise_vars(t_parser *vars, t_list *lst)
{
	vars->counter = 0;
	vars->state = STATE_DEFAULT;
	vars->cmd_arg_size = cmd_argument_size(lst);
	g_mini.command->cmd = _malloc(sizeof(char *) * (vars->cmd_arg_size + 1),'m');
	g_mini.command->cmd[vars->cmd_arg_size] = NULL;
	vars->tmp_cmd = g_mini.command;
}
void	parser(t_list *lst)
{
	t_parser	vars;

	intialise_vars(&vars, lst);
	while (lst != NULL)
	{
		if (lst->type == WORD && vars.counter <= vars.cmd_arg_size)
			handle_word_token(&vars, lst);
		if (lst->type == INRED || lst->type == OUTRED || lst->type == APPEND
			|| lst->type == HEREDOC)
			vars.state = STATE_REDIRECTION;
		else if (lst->type == PIPE)
			create_next_command_token(&vars, lst);
		if (lst != NULL)
			lst = lst->next;
	}
}
