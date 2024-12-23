/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:19:36 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 23:02:59 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(t_list *token)
{
	if (!token)
		return (0);
	return (token->type == PIPE || token->type == INRED || token->type == OUTRED
		|| token->type == APPEND || token->type == HEREDOC);
}

t_error	create_error(t_error_type type, char *token)
{
	t_error	error;

	error.type = type;
	if (token)
		error.token = ft_strdup(token);
	else
		error.token = NULL;
	return (error);
}

t_error	check_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	if (!str)
		return (create_error(NO_ERROR, NULL));
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
