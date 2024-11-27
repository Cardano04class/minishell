/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:24:12 by mamir             #+#    #+#             */
/*   Updated: 2024/11/27 18:10:09 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --- Helper Functions --- */

int ensure_buffer_space(t_parse_state *state, size_t needed)
{
    // More conservative growth strategy
    if (state->result_idx + needed >= state->result_size)
    {
        size_t new_size = state->result_size * 2;
        if (new_size < state->result_idx + needed)
            new_size = state->result_idx + needed + 1;

        char *new_buf = realloc(state->result, new_size);
        if (!new_buf)
            return (0);

        state->result = new_buf;
        state->result_size = new_size;
    }
    return (1);
}

void handle_quotes(t_parse_state *state)
{
    if (!ensure_buffer_space(state, 1))
        return;

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


void init_parse_state(t_parse_state *state, char *line, t_env *env)
{
    // Initialize with a slightly larger default buffer
    state->result_size = (ft_strlen(line) * 2) + 1;
    state->result = malloc(state->result_size);
    
    if (!state->result)
    {
        // Handle allocation failure
        state->result_size = 0;
        return;
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

char *remove_quotes(char *str)
{
    char *result;
    int i = 0, j = 0;
    int end;

    if (!str)
        return NULL;

    end = ft_strlen(str) - 1;

    // Handle empty string case
    if (end < 0)
    {
        result = malloc(1);
        if (!result)
            return NULL;
        result[0] = '\0';  // Return empty string
        return result;
    }

    result = malloc(end + 2);  // Allocate memory for the result
    if (!result)
        return NULL;

    // Skip leading quotes
    while ((str[i] == '"' || str[i] == '\'') && i <= end)
        i++;

    // Skip trailing quotes
    while ((str[end] == '"' || str[end] == '\'') && end >= i)
        end--;

    // Special case: if the string is entirely quotes (e.g., "")
    if (i > end)
    {
        result[0] = '\0';  // Empty result
        return result;
    }

    // Copy characters from str to result, excluding quotes
    while (i <= end)
    {
        result[j] = str[i];
        i++;
        j++;
    }

    result[j] = '\0'; // Null-terminate the result
    return result;
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

void handle_regular_var(t_parse_state *state)
{
    char var_name[256] = {0};
    size_t var_idx = 0;
    char *value = NULL;

    // Special case for lone $
    if (!state->line[state->i] || !ft_isalnum(state->line[state->i]))
    {
        if (!ensure_buffer_space(state, 1))
            return;
        state->result[state->result_idx++] = '$';
        return;
    }

    // Collect variable name
    while (state->line[state->i] && 
           (ft_isalnum(state->line[state->i]) || state->line[state->i] == '_') && 
           var_idx < sizeof(var_name) - 1)
    {
        var_name[var_idx++] = state->line[state->i++];
    }
    var_name[var_idx] = '\0';

    // Handle special variables
    if (strcmp(var_name, "?") == 0)
        value = "0";  // Default exit status
    else
        value = expand_variable(state->env, var_name);

    // Safely copy variable value
    if (value)
    {
        size_t value_len = ft_strlen(value);
        if (!ensure_buffer_space(state, value_len))
            return;

        ft_memcpy(&state->result[state->result_idx], value, value_len);
        state->result_idx += value_len;
    }
}

void process_char(t_parse_state *state)
{
    if (state->i >= ft_strlen(state->line))
        return;  // Avoid accessing beyond the string length

    if (state->line[state->i] == '\'' || state->line[state->i] == '\"')
    {
        handle_quotes(state);
    }
    else if (state->line[state->i] == '$' && !state->in_single_quote)
    {
        state->i++;
        handle_regular_var(state);  // Process regular variables (e.g., $HOME)
    }
    else
    {
        if (!ensure_buffer_space(state, 1))
            return;
        state->result[state->result_idx++] = state->line[state->i++];
    }
}


char *expand_variables(t_env *env, char *line)
{
    t_parse_state state;
    char *expanded_line;

    // Sanity check for input
    if (!line)
        return NULL;

    // Initialize parse state
    init_parse_state(&state, line, env);
    if (!state.result)
        return NULL;

    // Process the entire line
    while (line[state.i])
    {
        // Ensure space before processing
        if (!ensure_buffer_space(&state, 1))
        {
            free(state.result);
            return NULL;
        }

        // Process each character
        process_char(&state);
    }

    // Null-terminate the result
    if (!ensure_buffer_space(&state, 1))
    {
        free(state.result);
        return NULL;
    }
    state.result[state.result_idx] = '\0';

    // Store expanded line before potential quote removal
    expanded_line = state.result;

    // Remove quotes after expansion
    return remove_quotes(expanded_line);
}


/* --- Argument Processing --- */

int should_merge_with_next(char *current, char *next)
{
    if (!next)
        return (0);

    size_t cur_len = ft_strlen(current);
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

void expand(t_env *env, t_list **list)
{
    t_list *current;
    t_list *prev = NULL;  // To track the previous node
    char *expanded_line;
    char *final_line;

    current = *list;  // Start from the head of the list

    while (current)
    {
        // Skip empty quote nodes (""), which have no meaningful content
        if (strcmp(current->content, "") == 0)
        {
            t_list *to_free = current;
            current = current->next;

            // If the node to remove is the first node, update the head
            if (prev == NULL)
                *list = current;
            else
                prev->next = current;

            if (current != NULL)
                current->prev = prev;

            free(to_free->content);
            free(to_free);
            continue;  // Skip further processing for this iteration
        }
        // Handle the case of ""$"" (empty string with $ inside)
        if (strcmp(current->content, "\"$\"") == 0)
        {
            free(current->content);
            current->content = strdup("");  // Treat ""$"" as an empty string
            continue;  // Skip further processing for this iteration
        }
        // Expand variables in the current node's content
        expanded_line = expand_variables(env, current->content);

        // Handle the expanded line and ensure quotes are removed
        final_line = remove_quotes(expanded_line);
        free(expanded_line);
        free(current->content);
        current->content = final_line;

        // Merge "$" and "HOME" into "$HOME"
        if (prev != NULL && prev->content != NULL)
        {
            if ((prev->content[strlen(prev->content) - 1] == '"' || prev->content[strlen(prev->content) - 1] == '\'') &&
                current->content[0] != ' ' && current->content[0] != '"' && current->content[0] != '\'')
            {
                // Merge the "$" and "HOME"
                char *merged_content = merge_args(prev->content, current->content);
                free(prev->content);
                prev->content = merged_content;
                prev->next = current->next;
                if (current->next != NULL)
                    current->next->prev = prev;
                free(current->content);
                free(current);
                continue;  // Skip further processing for this iteration
            }
        }

        // Move to the next node
        prev = current;
        current = current->next;
    }
}
