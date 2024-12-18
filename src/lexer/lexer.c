/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:42:59 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 13:43:00 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_checks(char *str, t_list **lst, t_lexer *vars, int *i)
{
	if (vars->state == INITIAL)
		in_initial_state(str, *i, vars);
	if (vars->state == IN_WHITESPACE)
		in_whitespace_state(str, i, vars);
	if (vars->state == IN_SPECIAL)
		in_special_state(str, lst, vars, i);
}

void	state_machine_lex(char *str, t_list **lst, t_lexer *vars, int *i)
{
	while (str[*i] != '\0')
	{
		state_checks(str, lst, vars, i);
		if (vars->state == IN_WORD || vars->state == IN_QUOTE)
		{
			if (vars->state == IN_WORD)
			{
				in_word_state(str, lst, vars, i);
				if (quote_found(str, vars, i) || special_char_found(str[*i],
						vars))
					continue ;
				vars->state = INITIAL;
				*i -= 1;
			}
			else if (vars->state == IN_QUOTE)
			{
				in_quote_state(str, lst, vars, i);
				if (special_char_found(str[*i], vars))
					continue ;
				vars->state = INITIAL;
				*i -= 1;
			}
		}
		*i += 1;
	}
}

void	initialise_lexer_vars(t_lexer *vars)
{
	vars->start = 0;
	vars->state = INITIAL;
	vars->separated_by_space = 0;
}

void	lexer(char *str, t_list **lst)
{
	int		i;
	t_lexer	vars;

	i = 0;
	initialise_lexer_vars(&vars);
	state_machine_lex(str, lst, &vars, &i);
}
