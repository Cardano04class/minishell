/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:02:51 by mamir             #+#    #+#             */
/*   Updated: 2024/11/29 11:25:40 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --- Helper Functions --- */

int	ensure_buffer_space(t_parse_state *state, size_t needed)
{
	size_t	new_size;
	char	*new_buf;

	if (state->result_idx + needed < state->result_size)
		return (1);
	new_size = state->result_size * 2;
	if (new_size < state->result_idx + needed)
		new_size = state->result_idx + needed + 1;
	new_buf = realloc(state->result, new_size);
	if (!new_buf)
		return (0);
	state->result = new_buf;
	state->result_size = new_size;
	return (1);
}
void	handle_dollar_cases(t_parse_state *state)
{
	// Special case: lone $
	if (!state->line[state->i] || 
		!(ft_isalnum(state->line[state->i]) || state->line[state->i] == '_'))
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		
		if (!state->in_single_quote)
		{
			state->result[state->result_idx++] = '$';
		}
		return ;
	}
}

void	handle_quotes(t_parse_state *state)
{
	if (!ensure_buffer_space(state, 1))
		return ;
	if (state->line[state->i] == '\'' && !state->in_double_quote)
	{
		state->in_single_quote = !state->in_single_quote;
		state->result[state->result_idx++] = state->line[state->i++];
	}
	else if (state->line[state->i] == '\"' && !state->in_single_quote)
	{
		state->in_double_quote = !state->in_double_quote;
		state->result[state->result_idx++] = state->line[state->i++];
	}
	else
	{
		state->result[state->result_idx++] = state->line[state->i++];
	}
}


void	init_parse_state(t_parse_state *state, char *line, t_env *env)
{
	state->result_size = (ft_strlen(line) * 2) + 1;
	state->result = malloc(state->result_size);
	if (!state->result)
	{
		state->result_size = 0;
		return ;
	}
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->result_idx = 0;
	state->line = line;
	state->i = 0;
	state->env = env;
}

/* --- Quote Removal --- */

void process_quotes(t_quote_state *state)
{
    if ((state->str[state->i] == '\'' && !state->in_double) ||
        (state->str[state->i] == '\"' && !state->in_single))
    {
        if (state->str[state->i] == '\'')
            state->in_single = !state->in_single;
        else
            state->in_double = !state->in_double;
        state->i++;
    }
    else
    {
        state->result[state->j++] = state->str[state->i++];
    }
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		len;
	int		in_single;
	int		in_double;

	if (!str)
		return (NULL);

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;

	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (!((str[i] == '\'' && !in_double) || (str[i] == '\"' && !in_single)))
			result[j++] = str[i];
		i++;
	}

	result[j] = '\0';
	return (result);
}




/* --- Variable Expansion --- */

char *expand_variable(t_env *env, const char *var_name)
{
    t_env *current = env;
    while (current)
    {
        if (strcmp(current->key, var_name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

void copy_var_value(t_parse_state *state, char *value)
{
    size_t value_len;

    if (!value)
        return;

    value_len = ft_strlen(value);
    if (!ensure_buffer_space(state, value_len))
        return;

    ft_memcpy(&state->result[state->result_idx], value, value_len);
    state->result_idx += value_len;
}

void	handle_regular_var(t_parse_state *state)
{
	char	var_name[256];
	size_t	var_idx;
	char	*value;

	ft_memset(var_name, 0, sizeof(var_name));
	var_idx = 0;
	value = NULL;

	// Skip if in single quotes
	if (state->in_single_quote)
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		state->result[state->result_idx++] = '$';
		return ;
	}

	handle_dollar_cases(state);

	// Collect variable name
	while (state->line[state->i] && 
		   (ft_isalnum(state->line[state->i]) || state->line[state->i] == '_') &&
		   var_idx < sizeof(var_name) - 1)
	{
		var_name[var_idx++] = state->line[state->i++];
	}
	var_name[var_idx] = '\0';

	// Expand variable
	if (strcmp(var_name, "?") == 0)
		value = "0";
	else
		value = expand_variable(state->env, var_name);

	if (value)
	{
		size_t	value_len;

		value_len = ft_strlen(value);
		if (!ensure_buffer_space(state, value_len))
			return ;
		ft_memcpy(&state->result[state->result_idx], value, value_len);
		state->result_idx += value_len;
	}
}


void	process_char(t_parse_state *state)
{
	if (state->i >= ft_strlen(state->line))
		return ;

	if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
		handle_quotes(state);
	else if (state->line[state->i] == '$')
	{
		state->i++;
		handle_regular_var(state);
	}
	else
	{
		if (!ensure_buffer_space(state, 1))
			return ;
		state->result[state->result_idx++] = state->line[state->i++];
	}
}



char	*expand_variables(t_env *env, char *line)
{
	t_parse_state	state;
	char			*expanded_line;

	if (!line)
		return (NULL);

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

	if (!ensure_buffer_space(&state, 1))
	{
		free(state.result);
		return (NULL);
	}
	state.result[state.result_idx] = '\0';

	expanded_line = remove_quotes(state.result);
	free(state.result);

	return (expanded_line);
}



/* --- Argument Processing --- */

int	should_merge_with_next(char *current, char *next)
{
	size_t	cur_len;

	if (!next)
		return (0);

	cur_len = ft_strlen(current);
	return ((!ft_strchr("'\"", current[0]) && cur_len > 0 &&
			(current[cur_len - 1] == '\'' || current[cur_len - 1] == '\"')) ||
			(current[0] != '\'' && current[0] != '\"' &&
			 (next[0] == '\'' || next[0] == '\"')));
}

char *merge_args(char *arg1, char *arg2)
{
    char *merged;
    size_t len1 = ft_strlen(arg1);
    size_t len2 = ft_strlen(arg2);

    merged = malloc(len1 + len2 + 1);  // Allocate space for the combined string
    if (!merged)
        return NULL;

    ft_strlcpy(merged, arg1, len1 + 1);  // Copy first argument
    ft_strlcat(merged, arg2, len1 + len2 + 1);  // Concatenate the second argument

    return merged;
}

/* --- Main Expand Function --- */


void	expand(t_env *env, t_list **list)
{
	t_list	*current;
	t_list	*prev;
	char	*expanded_line;
	char	*final_line;
	int		was_modified;

	current = *list;
	prev = NULL;

	while (current)
	{
		// Skip empty strings
		if (strcmp(current->content, "") == 0)
		{
			prev = current;
			current = current->next;
			continue ;
		}

		// Track if this node was modified by expansion or quote removal
		was_modified = 0;

		expanded_line = expand_variables(env, current->content);

		if (!expanded_line)
		{
			free(current->content);
			current->content = ft_strdup("");
			was_modified = 1;
		}
		else
		{
			final_line = remove_quotes(expanded_line);
			free(expanded_line);

			// Only mark as modified if content actually changed
			if (strcmp(final_line, current->content) != 0)
				was_modified = 1;

			free(current->content);
			current->content = final_line;
		}

		// Refined merging logic that only merges based on original parsing
		if (prev && !was_modified && 
			strcmp(prev->content, "") != 0 && 
			strcmp(current->content, "") != 0 && 
			should_merge_with_next(prev->content, current->content))
		{
			char *merged = merge_args(prev->content, current->content);
			free(prev->content);
			prev->content = merged;

			t_list *to_free = current;
			prev->next = current->next;
			if (current->next)
				current->next->prev = prev;
			current = current->next;

			free(to_free->content);
			free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
