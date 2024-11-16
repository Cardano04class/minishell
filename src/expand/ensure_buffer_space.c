/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ensure_buffer_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:40:46 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:40:56 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ensure_buffer_space(t_parse_state *state, size_t needed)
{
	char	*new_buf;
	size_t	new_size;

	if (state->result_idx + needed >= state->result_size)
	{
		new_size = state->result_size * 2;
		new_buf = malloc(new_size);
		if (!new_buf)
			return (0);
		ft_memcpy(new_buf, state->result, state->result_idx);
		free(state->result);
		state->result = new_buf;
		state->result_size = new_size;
	}
	return (1);
}
