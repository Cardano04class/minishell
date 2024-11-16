/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_regular_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:39:15 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:39:26 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_regular_var(t_parse_state *state)
{
	char	var_name[256];
	size_t	var_idx;
	char	*value;

	var_idx = 0;
	while (ft_isalnum(state->line[state->i]) || state->line[state->i] == '_')
	{
		if (var_idx < 255)
			var_name[var_idx++] = state->line[state->i];
		state->i++;
	}
	var_name[var_idx] = '\0';
	value = expand_variable(state->env, var_name);
	copy_var_value(state, value);
}
