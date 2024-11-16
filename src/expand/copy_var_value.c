/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_var_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:39:36 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:39:46 by mamir            ###   ########.fr       */
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
