/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:51:58 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:52:22 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quoted_var(t_parse_state *state, char quote_char)
{
	char	literal_value[256];
	size_t	literal_idx;

	literal_idx = 0;
	state->i++;
	while (state->line[state->i] && state->line[state->i] != quote_char
		&& literal_idx < 255)
	{
		literal_value[literal_idx] = state->line[state->i];
		literal_idx++;
		state->i++;
	}
	if (state->line[state->i] == quote_char)
		state->i++;
	literal_value[literal_idx] = '\0';
	if (!ensure_buffer_space(state, literal_idx + 2))
		return ;
	state->result[state->result_idx++] = quote_char;
	ft_memcpy(&state->result[state->result_idx], literal_value, literal_idx);
	state->result_idx += literal_idx;
	state->result[state->result_idx++] = quote_char;
}
