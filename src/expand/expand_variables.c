/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:35 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:38:45 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(t_env *env, char *line)
{
	t_parse_state	state;

	init_parse_state(&state, line, env);
	if (!state.result)
		return (NULL);
	while (line[state.i])
	{
		if (line[state.i] == '\'' || line[state.i] == '\"')
			handle_quotes(&state);
		else if (line[state.i] == '$' && !state.in_single_quote)
			expand_env_var(&state);
		else
			state.result[state.result_idx++] = line[state.i++];
	}
	state.result[state.result_idx] = '\0';
	return (state.result);
}
