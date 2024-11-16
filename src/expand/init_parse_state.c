/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:40:22 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:40:33 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parse_state(t_parse_state *state, char *line, t_env *env)
{
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->result = malloc(BUFFER_SIZE);
	state->result_size = BUFFER_SIZE;
	state->result_idx = 0;
	state->line = line;
	state->i = 0;
	state->env = env;
}
