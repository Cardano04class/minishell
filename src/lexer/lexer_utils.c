/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:39:33 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:09:02 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_token(char *str, int start, int end)
{
	return (ft_substr(str, start, end - start));
}

int	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	quote_found(char *str, t_lexer *vars, int *i)
{
	if (str[*i] == 34 || str[*i] == 39)
	{
		vars->quote_char = str[*i];
		vars->state = IN_QUOTE;
		vars->start = *i;
		return (1);
	}
	return (0);
}

int	special_char_found(char c, t_lexer *vars)
{
	if (is_special_char(c))
	{
		vars->state = IN_SPECIAL;
		return (1);
	}
	return (0);
}
