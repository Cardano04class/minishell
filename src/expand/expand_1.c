/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:23:26 by mamir             #+#    #+#             */
/*   Updated: 2024/11/26 18:03:15 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	shift_left(int i)
{
	while (g_mini.command->cmd[i + 1])
	{
		g_mini.command->cmd[i] = g_mini.command->cmd[i + 1];
		i++;
	}
	g_mini.command->cmd[i] = NULL;
}

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

void handle_quotes(t_parse_state *state)
{
    if (!ensure_buffer_space(state, 1))
        return ;
    if (state->line[state->i] == '\'' && !state->in_double_quote)
    {
        state->in_single_quote = !state->in_single_quote;
        // Keep the quote in the result for proper removal later
        state->result[state->result_idx++] = state->line[state->i];
    }
    else if (state->line[state->i] == '\"' && !state->in_single_quote)
    {
        state->in_double_quote = !state->in_double_quote;
        // Keep the quote in the result for proper removal later
        state->result[state->result_idx++] = state->line[state->i];
    }
    else
    {
        state->result[state->result_idx++] = state->line[state->i];
    }
    state->i++;
}
