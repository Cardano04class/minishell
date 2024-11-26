/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:24:12 by mamir             #+#    #+#             */
/*   Updated: 2024/11/26 20:43:51 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty_arg(int i)
{
	free(g_mini.command->cmd[i]);
	shift_left(i);
}

void	process_expanded(int i, char *expanded_line)
{
	char	*final_line;

	if (!expanded_line)
		return ;
	final_line = remove_quotes(expanded_line);
	free(expanded_line);
	if (!final_line)
	{
		free(g_mini.command->cmd[i]);
		shift_left(i);
		return ;
	}
	free(g_mini.command->cmd[i]);
	g_mini.command->cmd[i] = final_line;
}

char	*expand_variables(t_env *env, char *line)
{
	t_parse_state	state;

	init_parse_state(&state, line, env);
	if (!state.result)
		return (NULL);
	while (line[state.i])
	{
		if (!ensure_buffer_space(&state, 1))
		{
			free(state.result);
			return (NULL);
		}
		process_char(&state);
	}
	state.result[state.result_idx] = '\0';
	return (state.result);
}

void	handle_merged_arg(int *i)
{
	char	*next_arg;
	char	*merged_arg;

	next_arg = g_mini.command->cmd[*i + 1];
	if (next_arg[0] == '\"' || next_arg[0] == '\'')
	{
		merged_arg = malloc(ft_strlen(next_arg) + 2);
		if (!merged_arg)
			return ;
		strcpy(merged_arg, "$");
		strcat(merged_arg, next_arg);
		free(g_mini.command->cmd[*i]);
		g_mini.command->cmd[*i] = merged_arg;
		shift_left(*i + 1);
	}
}

void	expand(t_env *env)
{
	int		i;
	char	*line;
	char	*expanded_line;

	i = 0;
	while (g_mini.command->cmd[i])
	{
		line = g_mini.command->cmd[i];
		if (line[0] == '$' && line[1] == '\0' && g_mini.command->cmd[i + 1])
			handle_merged_arg(&i);
		expanded_line = expand_variables(env, g_mini.command->cmd[i]);
		process_expanded(i, expanded_line);
		i++;
	}
}
