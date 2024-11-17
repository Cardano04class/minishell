/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:29:25 by mamir             #+#    #+#             */
/*   Updated: 2024/11/17 10:37:39 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_value(t_parse_state *state, char *value)
{
	size_t	value_len;

	if (!value)
		return ;
	value_len = ft_strlen(value);
	if (!ensure_buffer_space(state, value_len))
		return ;
	ft_memcpy(&state->result[state->result_idx], value, value_len);
	state->result_idx += value_len;
}

void	handle_quoted_var(t_parse_state *state, char quote_char)
{
	char	literal_value[256];
	size_t	literal_idx;

	literal_idx = 0;
	state->i++;
	while (state->line[state->i] && state->line[state->i] != quote_char
		&& literal_idx < 255)
		literal_value[literal_idx++] = state->line[state->i++];
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

void	handle_regular_var(t_parse_state *state)
{
	char	var_name[256];
	size_t	var_idx;
	char	*value;

	var_idx = 0;
	if (!state->line[state->i])
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		state->result[state->result_idx++] = '$';
		return ;
	}
	while (state->line[state->i] && (ft_isalnum(state->line[state->i])
			|| state->line[state->i] == '_') && var_idx < 255)
		var_name[var_idx++] = state->line[state->i++];
	var_name[var_idx] = '\0';
	if (var_idx > 0)
	{
		value = expand_variable(state->env, var_name);
		copy_var_value(state, value);
	}
	else if (!ensure_buffer_space(state, 1))
		return ;
	else
		state->result[state->result_idx++] = '$';
}

void	expand_env_var(t_parse_state *state)
{
	state->i++;
	if (!state->line[state->i] || state->line[state->i] == ' '
		|| state->line[state->i] == '\t')
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		state->result[state->result_idx++] = '$';
		return ;
	}
	if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
		handle_quoted_var(state, state->line[state->i]);
	else
		handle_regular_var(state);
}

void	process_standard_char(t_parse_state *state)
{
	if (!ensure_buffer_space(state, 1))
		return ;
	state->result[state->result_idx++] = state->line[state->i++];
}
