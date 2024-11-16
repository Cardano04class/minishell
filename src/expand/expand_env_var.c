/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:55 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:39:05 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env_var(t_parse_state *state)
{
	state->i++;
	if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
		handle_quoted_var(state, state->line[state->i]);
	else
		handle_regular_var(state);
}
