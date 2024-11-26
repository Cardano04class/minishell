/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:37:15 by mamir             #+#    #+#             */
/*   Updated: 2024/11/26 17:37:58 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(t_list *token)
{
	if (token->type == PIPE || token->type == INRED
		|| token->type == OUTRED || token->type == APPEND
		|| token->type == HEREDOC)
		return (1);
	return (0);
}

t_error	check_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
		return (create_error(UNCLOSED_QUOTES, str));
	return (create_error(NO_ERROR, NULL));
}
	
t_error	check_special_token_position(t_list *token)
{
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

void	syntax_error(t_list *list)
{
	t_error	error;

	error = syntax_check(list);
	if (error.type != NO_ERROR)
		print_error(error);
}
