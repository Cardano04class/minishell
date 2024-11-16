/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/11/13 14:26:34 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 1024

static char	*expand_variable(t_env *env, const char *var_name)
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

static void	shift_left(int i)
{
	while (g_mini.command->cmd[i + 1])
	{
		g_mini.command->cmd[i] = g_mini.command->cmd[i + 1];
		i++;
	}
	g_mini.command->cmd[i] = NULL;
}

static int	ensure_buffer_space(t_parse_state *state, size_t needed)
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

static void	init_parse_state(t_parse_state *state, char *line, t_env *env)
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

static void handle_quotes(t_parse_state *state)
{
    if (!ensure_buffer_space(state, 1))
        return;
    if (state->line[state->i] == '\'' && !state->in_double_quote)
    {
        state->in_single_quote = !state->in_single_quote;
        state->result[state->result_idx++] = state->line[state->i];
    }
    else if (state->line[state->i] == '\"' && !state->in_single_quote)
    {
        state->in_double_quote = !state->in_double_quote;
        state->result[state->result_idx++] = state->line[state->i];
    }
    else
    {
        state->result[state->result_idx++] = state->line[state->i];
    }
    state->i++;
}

static void	copy_var_value(t_parse_state *state, char *value)
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

static void expand_env_var(t_parse_state *state)
{
    char literal_value[256];
    size_t literal_idx = 0;
    char *value;
    char quote_char;

    state->i++; // Skip the '$'

    // Check if next character is a single or double quote
    if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
    {
        // Store the type of quote (single or double)
        quote_char = state->line[state->i++];
        
        // Copy characters until we reach the same closing quote
        while (state->line[state->i] && state->line[state->i] != quote_char && literal_idx < 255)
        {
            literal_value[literal_idx++] = state->line[state->i++];
        }
        
        // Skip the closing quote if present
        if (state->line[state->i] == quote_char)
            state->i++;
        
        // Null-terminate the literal string
        literal_value[literal_idx] = '\0';

        // Ensure space in result buffer and copy the literal value with quotes
        if (!ensure_buffer_space(state, literal_idx + 2))
            return;
        
        // Add the literal value surrounded by the original quotes
        state->result[state->result_idx++] = quote_char;
        ft_memcpy(&state->result[state->result_idx], literal_value, literal_idx);
        state->result_idx += literal_idx;
        state->result[state->result_idx++] = quote_char;
        
        return;
    }

    // Regular variable expansion
    char var_name[256];
    size_t var_idx = 0;
    
    while (state->line[state->i] && (ft_isalnum(state->line[state->i]) || state->line[state->i] == '_') && var_idx < 255)
    {
        var_name[var_idx++] = state->line[state->i++];
    }
    var_name[var_idx] = '\0';

    if (var_idx > 0)
    {
        value = expand_variable(state->env, var_name);
        copy_var_value(state, value);
    }
    else
    {
        // In case of no variable name, add a literal '$'
        if (!ensure_buffer_space(state, 1))
            return;
        state->result[state->result_idx++] = '$';
    }
}


char    *expand_variables(t_env *env, char *line)
{
    t_parse_state    state;

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
        if (line[state.i] == '\'' || line[state.i] == '\"')
        {
            handle_quotes(&state);
            continue;
        }
        if (line[state.i] == '$' && !state.in_single_quote)
        {
            expand_env_var(&state);
            continue;
        }
        state.result[state.result_idx++] = line[state.i++];
    }
    state.result[state.result_idx] = '\0';
    return (state.result);
}

char	*remove_quotes(char *str)
{
	char	*result;
	size_t	i;
	size_t	j;
	int		in_quotes[2];

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes[0] = 0;
	in_quotes[1] = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_quotes[1])
			in_quotes[0] = !in_quotes[0];
		else if (str[i] == '\"' && !in_quotes[0])
			in_quotes[1] = !in_quotes[1];
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void    process_expanded(int i, char *expanded_line)
{
    char    *final_line;

    if (!expanded_line)
        return;
    final_line = remove_quotes(expanded_line);
    free(expanded_line);
    if (!final_line)
    {
        free(g_mini.command->cmd[i]);
        shift_left(i);
        return;
    }
    free(g_mini.command->cmd[i]);
    g_mini.command->cmd[i] = final_line;
}

void	remove_empty_arg(int i)
{
	free(g_mini.command->cmd[i]);
	shift_left(i);
}

void expand(t_env *env)
{
    int i = 0;
    char *line;
    char *merged_arg = NULL;
    char *expanded_line;

    while (g_mini.command->cmd[i])
    {
        line = g_mini.command->cmd[i];
        if (line[0] == '$' && line[1] == '\0' && g_mini.command->cmd[i + 1])
        {
            char *next_arg = g_mini.command->cmd[i + 1];
            if (next_arg[0] == '\"' || next_arg[0] == '\'')
            {
                merged_arg = malloc(ft_strlen(next_arg) + 2);
                if (!merged_arg)
                    return;
                strcpy(merged_arg, "$");
                strcat(merged_arg, next_arg);
                free(g_mini.command->cmd[i]);
                g_mini.command->cmd[i] = merged_arg;
                shift_left(i + 1);
            }
        }
        expanded_line = expand_variables(env, g_mini.command->cmd[i]);
        process_expanded(i, expanded_line);
        i++;
    }
}
