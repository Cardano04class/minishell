/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:39:58 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:40:10 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(t_parse_state *state)
{
	if (!ensure_buffer_space(state, 1))
		return ;
	if (state->line[state->i] == '\'' && !state->in_double_quote)
		state->in_single_quote = !state->in_single_quote;
	else if (state->line[state->i] == '\"' && !state->in_single_quote)
		state->in_double_quote = !state->in_double_quote;
	else
		state->result[state->result_idx++] = state->line[state->i];
	state->i++;
}
