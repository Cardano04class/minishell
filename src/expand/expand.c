/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:02:51 by mamir             #+#    #+#             */
/*   Updated: 2024/11/29 11:44:02 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --- Helper Functions --- */
void merge_export_assignment(t_list **list)
{
    t_list *current = *list;

    while (current && current->next)
    {
        // If the current node is "export" and the next node contains a variable assignment
        if (strcmp(current->content, "export") == 0 && 
            current->next && current->next->content &&
            strchr(current->next->content, '='))  // Ensure the next node contains an '='
        {
            // The next node should contain the variable assignment (e.g., a=ls -la)
            char *var_assignment = current->next->content;

            // Check if the variable assignment has quotes around it
            if (var_assignment[0] == '"' || var_assignment[0] == '\'')
            {
                // Remove the surrounding quotes from the assignment value
                var_assignment = remove_quotes(var_assignment);
            }

            // Allocate enough space for "export" + space + variable assignment (e.g., a=ls -la)
            size_t export_len = strlen(current->content);
            size_t var_len = strlen(var_assignment);

            char *merged_content = malloc(export_len + var_len + 2); // +2 for space and null terminator
            if (merged_content)
            {
                // Copy "export "
                memcpy(merged_content, current->content, export_len);
                merged_content[export_len] = ' '; // Add a space between "export" and the variable assignment

                // Copy the variable assignment
                memcpy(merged_content + export_len + 1, var_assignment, var_len);
                merged_content[export_len + var_len + 1] = '\0'; // Null terminate the string

                // Replace the content of the "export" node with the merged content
                free(current->content);
                current->content = merged_content;

                // Remove the next node (the variable assignment)
                t_list *to_free = current->next;
                current->next = to_free->next;
                if (to_free->next)
                    to_free->next->prev = current;
                free(to_free->content);
                free(to_free);
            }
        }
        // Move to the next node
        current = current->next;
    }
}


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

	// First, merge export assignments
	merge_export_assignment(list);

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

		// Handle the expansion of variables in the content
		expanded_line = expand_variables(env, current->content);

		if (!expanded_line)
		{
			free(current->content);
			current->content = ft_strdup("");
			was_modified = 1;
		}
		else
		{
			// Handle export case: if we are processing an export variable assignment, 
			// we should keep the quotes around the value for assignment but remove them 
			// for further expansion (e.g., "ls -la" -> ls -la).
			if (strncmp(current->content, "export ", 7) == 0)
			{
				// Remove the quotes from the value part of the assignment
				char *eq_pos = strchr(expanded_line, '=');
				if (eq_pos)
				{
					char *value_start = eq_pos + 1;
					// Check if the value is surrounded by quotes and remove them
					if ((*value_start == '"' || *value_start == '\'') &&
						*(value_start + strlen(value_start) - 1) == *value_start)
					{
						// Remove the surrounding quotes
						value_start++;
						*(value_start + strlen(value_start) - 1) = '\0';
					}

					// Reconstruct the expanded line
					char *new_expanded_line = malloc(strlen(current->content) + strlen(value_start) + 2);
					if (new_expanded_line)
					{
						snprintf(new_expanded_line, strlen(current->content) + strlen(value_start) + 2, "%s=%s", current->content + 7, value_start);
						free(expanded_line);
						expanded_line = new_expanded_line;
					}
				}
			}

			// Remove quotes in general if necessary
			final_line = remove_quotes(expanded_line);
			free(expanded_line);

			// Only mark as modified if the content actually changed
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
