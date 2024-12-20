/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_machine_states.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:08:33 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/19 02:16:14 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_initial_state(char *str, int i, t_lexer *vars)
{
	if (ft_isspace(str[i]))
	{
		vars->state = IN_WHITESPACE;
		vars->separated_by_space = 1;
	}
	else if (is_special_char(str[i]))
		vars->state = IN_SPECIAL;
	else if (str[i] == 34 || str[i] == 39)
	{
		vars->quote_char = str[i];
		vars->state = IN_QUOTE;
		vars->start = i;
	}
	else
	{
		vars->state = IN_WORD;
		vars->start = i;
	}
}

void	in_whitespace_state(char *str, int *i, t_lexer *vars)
{
	while (ft_isspace(str[*i]))
		*i += 1;
	vars->state = INITIAL;
	*i -= 1;
}

void	in_special_state(char *str, t_list **lst, t_lexer *vars, int *i)
{
	if (str[*i] == '|')
		ft_lstaddback(lst, ft_lstnew_2(ft_strdup("|"), PIPE,
				vars->separated_by_space));
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		ft_lstaddback(lst, ft_lstnew_2(ft_strdup(">>"), APPEND,
				vars->separated_by_space));
		*i += 1;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		ft_lstaddback(lst, ft_lstnew_2(ft_strdup("<<"), HEREDOC,
				vars->separated_by_space));
		*i += 1;
	}
	else if (str[*i] == '>')
		ft_lstaddback(lst, ft_lstnew_2(ft_strdup(">"), OUTRED,
				vars->separated_by_space));
	else if (str[*i] == '<')
		ft_lstaddback(lst, ft_lstnew_2(ft_strdup("<"), INRED,
				vars->separated_by_space));
	vars->state = INITIAL;
	vars->separated_by_space = 0;
}

void	in_word_state(char *str, t_list **lst, t_lexer *vars, int *i)
{
	while (str[*i] != '\0' && !is_special_char(str[*i]) && !ft_isspace(str[*i])
		&& str[*i] != 34 && str[*i] != 39)
		*i += 1;
	ft_lstaddback(lst, ft_lstnew_2(create_token(str, vars->start, *i), WORD,
			vars->separated_by_space));
	vars->separated_by_space = 0;
}

void	in_quote_state(char *str, t_list **lst, t_lexer *vars, int *i)
{
	*i += 1;
	while (str[*i] != '\0' && str[*i] != vars->quote_char)
		*i += 1;
	if (str[*i] == vars->quote_char)
		*i += 1;
	ft_lstaddback(lst, ft_lstnew_2(create_token(str, vars->start, *i), WORD,
			vars->separated_by_space));
	vars->separated_by_space = 0;
}
