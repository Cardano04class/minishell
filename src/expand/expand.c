/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/11/06 16:30:49 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 1024

void toggle_quote(char quote_char, int *in_single_quote, int *in_double_quote) {
    if (quote_char == '\'') {
        // Toggle the single quote state
        *in_single_quote = !(*in_single_quote);
    } else if (quote_char == '\"') {
        // Toggle the double quote state
        *in_double_quote = !(*in_double_quote);
    }
}

char *expand_variable(t_env *env, const char *var_name) {
    t_env *current = env;
    while (current) {
        if (strcmp(current->key, var_name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Return NULL if the variable is not found
}

char *expand_variables(t_env *env, char *line) {
    char *result = malloc(1024); // Buffer for expanded result
    if (!result) return NULL;

    int result_idx = 0;
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (line[i]) {
        // Toggle quotes
        if (line[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            result[result_idx++] = line[i++];
            continue;
        } else if (line[i] == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            result[result_idx++] = line[i++];
            continue;
        }
        // Variable expansion (skip inside single quotes)
        if (line[i] == '$' && !in_single_quote) {
            i++; // Skip the '$'
            char var_name[100];
            int var_idx = 0;

            // Capture the variable name (alphanumeric + '_')
            while (line[i] && (isalnum(line[i]) || line[i] == '_')) {
                var_name[var_idx++] = line[i++];
            }
            var_name[var_idx] = '\0'; // Null-terminate the variable name
            // Get the variable value from the environment
            char *var_value = expand_variable(env, var_name);
            if (var_value) 
            {
                strcpy(&result[result_idx], var_value);
                result_idx += strlen(var_value);
            }
            continue;
        }
        
        // Copy normal characters
        result[result_idx++] = line[i++];
    }

    result[result_idx] = '\0';
    return result;
}

// Function to handle and remove quotes from a string
char *handle_quotes(const char *str)
{
    if (!str)
        return NULL;

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (!result)
        return NULL;

    int i = 0, j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_double_quote)
        {
            // Toggle single quotes and only skip if fully enclosing
            if (in_single_quote && str[i + 1] == '\0') {
                in_single_quote = 0;
                i++;
                continue;
            }
            if (!in_single_quote && j == 0 && str[i + 1] != '\0') {
                in_single_quote = 1;
                i++;
                continue;
            }
            result[j++] = str[i];
        }
        else if (str[i] == '\"' && !in_single_quote)
        {
            // Toggle double quotes and only skip if fully enclosing
            if (in_double_quote && str[i + 1] == '\0') {
                in_double_quote = 0;
                i++;
                continue;
            }
            if (!in_double_quote && j == 0 && str[i + 1] != '\0') {
                in_double_quote = 1;
                i++;
                continue;
            }
            result[j++] = str[i];
        }
        else
        {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';

    // If all quotes were stripped, return an empty string to avoid incorrect behavior
    if (j == 0)
    {
        free(result);
        return strdup("");
    }

    return result;
}




// Function to expand commands in the mini shell
void expand(t_env *env)
{
    int i = 0;
    char *line;
    char *expanded_line;
    char *final_line;

    while (g_mini.command->cmd[i])
    {
        line = g_mini.command->cmd[i];

        // Expand variables
        expanded_line = expand_variables(env, line);
        if (!expanded_line) {
            // Handle memory allocation failure or any other issues
            continue;
        }

        // Handle quotes while preserving literals
        final_line = handle_quotes(expanded_line);
        free(expanded_line); // Free the expanded line, as it's no longer needed

        // Replace the original command string with the final processed string
        free(g_mini.command->cmd[i]);
        g_mini.command->cmd[i] = final_line;

        i++;
    }
}

