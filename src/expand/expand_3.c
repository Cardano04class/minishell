/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:30:29 by mamir             #+#    #+#             */
/*   Updated: 2024/11/26 18:03:15 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_char(t_parse_state *state)
{
	if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
	{
		handle_quotes(state);
		return ;
	}
	if (state->line[state->i] == '$' && !state->in_single_quote)
	{
		expand_env_var(state);
		return ;
	}
	process_standard_char(state);
}

void process_quotes(t_quote_state *state)
{
    if ((state->str[state->i] == '\'' && !state->in_double) ||
        (state->str[state->i] == '\"' && !state->in_single))
    {
        if (state->str[state->i] == '\'')
            state->in_single = !state->in_single;
        else
            state->in_double = !state->in_double;
        // Skip the quote without adding space
        state->i++;
    }
    else
    {
        // Copy character without adding space
        state->result[state->j++] = state->str[state->i++];
    }
}

char *remove_quotes(char *str)
{
    t_quote_state state;

    if (!str)
        return (NULL);
    state.result = malloc(ft_strlen(str) + 1);
    if (!state.result)
        return (NULL);
    state.str = str;
    state.i = 0;
    state.j = 0;
    state.in_single = 0;
    state.in_double = 0;
    while (str[state.i])
        process_quotes(&state);
    state.result[state.j] = '\0';
    return (state.result);
}
