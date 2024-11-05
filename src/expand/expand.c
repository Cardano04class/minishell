/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/11/05 22:41:32 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 1024


// Main function to expand variables and handle quotes in input
char *expand_variables(t_env *env, char *line)
{
    char *result;
    int result_idx = 0;
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    result = malloc(BUFFER_SIZE);  // Allocate buffer size
    if (!result)
        return NULL;

    while (line[i])
    {
        // Handle single quotes
        if (line[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            result[result_idx++] = line[i++];
            continue;
        }

        // Handle double quotes
        if (line[i] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            result[result_idx++] = line[i++];
            continue;
        }

        // Handle variable expansion only if not in single quote
        if (line[i] == '$' && !in_single_quote)
        {
            i++;
            char var_name[100];
            int var_idx = 0;
            
            // Capture variable name
            while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
            {
                var_name[var_idx++] = line[i++];
            }
            var_name[var_idx] = '\0';

            // Get variable value
            if (var_idx > 0)
            {
                char *var_value = get_env(env, var_name);
                if (var_value)
                {
                    // Copy value into result
                    strcpy(&result[result_idx], var_value);
                    result_idx += strlen(var_value);
                }
            }
            continue;
        }

        // Normal character addition
        result[result_idx++] = line[i++];
    }

    result[result_idx] = '\0';  // Null-terminate result
    return result;
}

// Function to handle and remove quotes from a string
char *handle_quotes(char *str)
{
    char *result;
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (!str)
        return NULL;

    result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;

    // Process each character of the string
    while (str[i])
    {
        // Toggle quotes
        if (str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        }
        if (str[i] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        }

        // Append character to result
        result[j++] = str[i++];
    }

    result[j] = '\0';  // Null-terminate result

    // Return empty string if no content
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
        expanded_line = expand_variables(env, line);
        if (expanded_line)
        {
            final_line = handle_quotes(expanded_line);
            free(expanded_line);
            if (final_line[0] == '\0')
            {
                free(final_line);
                int j = i;
                free(g_mini.command->cmd[i]);
                while (g_mini.command->cmd[j + 1])
                {
                    g_mini.command->cmd[j] = g_mini.command->cmd[j + 1];
                    j++;
                }
                g_mini.command->cmd[j] = NULL;
                continue;
            }
            free(g_mini.command->cmd[i]);
            g_mini.command->cmd[i] = final_line;
        }
        i++;
    }
}
