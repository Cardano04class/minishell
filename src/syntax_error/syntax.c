/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:30:33 by mamir             #+#    #+#             */
/*   Updated: 2024/12/20 09:10:07 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	check_special_token_position(t_list *token)
{
	if (!token)
		return (create_error(NO_ERROR, NULL));
	if (!token->next && is_special(token))
		return (create_error(MISSING_CONTEXT, token->content));
	if (!token->prev && token->type == PIPE)
		return (create_error(PIPE_AT_START, token->content));
	if (token->next && is_special(token) && is_special(token->next))
		return (create_error(CONSECUTIVE_SPECIAL, token->content));
	return (create_error(NO_ERROR, NULL));
}

t_error	syntax_check(t_list *list)
{
	t_error	error;

	error.type = NO_ERROR;
	error.token = NULL;
	while (list)
	{
		if (list->type == WORD)
		{
			error = check_quotes(list->content);
			if (error.type != NO_ERROR)
				return (error);
		}
		if (is_special(list))
		{
			error = check_special_token_position(list);
			if (error.type != NO_ERROR)
				return (error);
		}
		list = list->next;
	}
	return (create_error(NO_ERROR, NULL));
}

void	print_error(t_error error)
{
	if (error.type == UNCLOSED_QUOTES)
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
	else if (error.type == INVALID_POSITION || error.type == PIPE_AT_START
		|| error.type == MISSING_CONTEXT)
	{
		ft_putstr_fd("syntax error: '", 2);
		if (error.token)
			ft_putstr_fd(error.token, 2);
		else
			ft_putstr_fd("(null)", 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error.type == CONSECUTIVE_SPECIAL)
		ft_putstr_fd("syntax error: consecutive special symbols\n", 2);
	else
		ft_putstr_fd("syntax error: unknown error\n", 2);
}

int	syntax_error(t_list *list)
{
	t_error	error;

	error = syntax_check(list);
	if (error.type != NO_ERROR)
	{
		print_error(error);
		if (error.type == UNCLOSED_QUOTES || error.type == INVALID_POSITION
			|| error.type == PIPE_AT_START || error.type == MISSING_CONTEXT
			|| error.type == CONSECUTIVE_SPECIAL)
		{
			g_mini.exit_status = 2;
		}
		else
		{
			g_mini.exit_status = 1;
		}
		return (1);
	}
	return (0);
}
