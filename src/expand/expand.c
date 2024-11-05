/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/11/05 23:09:33 by mamir            ###   ########.fr       */
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

void expand_variable(t_expand_var_params *params)
{
    char var_name[100];
    int var_idx = 0;
    int i = *(params->index);  // Use the correct index

    // Process the variable (expand it) as before
    while (params->line[i] && (ft_isalnum(params->line[i]) || params->line[i] == '_'))
    {
        var_name[var_idx++] = params->line[i++];
    }
    var_name[var_idx] = '\0';

    // Expand variable (if found) and add to result
    if (var_idx > 0)
    {
        char *var_value = get_env(params->env, var_name);
        if (var_value)
        {
            strcpy(&params->result[*(params->result_idx)], var_value);
            *(params->result_idx) += strlen(var_value);
        }
    }

    *(params->index) = i;  // Update the index
}

// Main function to expand variables and handle quotes in input
void expand_variables(t_env *env, char *line, char *result)
{
    int result_idx = 0;
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    t_expand_var_params params;

    // Initialize struct
    params.line = line;
    params.index = &i;
    params.env = env;
    params.result = result;
    params.result_idx = &result_idx;

    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            toggle_quote(line[i], &in_single_quote, &in_double_quote);
            i++;
            continue;
        }

        if (line[i] == '$' && !in_single_quote)
        {
            expand_variable(&params);  // Pass struct to the function
        }
        else
        {
            result[result_idx++] = line[i++];
        }
    }

    result[result_idx] = '\0';  // Null-terminate the string
}





// Function to handle and remove quotes from a string
char *handle_quotes(char *str)
{
    if (!str)
        return NULL;

    char *result;
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;

    while (str[i])
    {
        // Handle single and double quotes
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

        // Add non-quote characters to the result
        result[j++] = str[i++];
    }

    result[j] = '\0';

    // If the resulting string is empty, return an empty string instead of NULL
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
    char expanded_line[BUFFER_SIZE];  // Make sure this is large enough

    while (g_mini.command->cmd[i])
    {
        line = g_mini.command->cmd[i];

        // Call expand_variables with a result buffer
        expand_variables(env, line, expanded_line);

        // Handle the expanded line (quotes, etc.)
        char *final_line = handle_quotes(expanded_line);

        free(g_mini.command->cmd[i]);
        g_mini.command->cmd[i] = final_line;

        // If empty string, remove the command
        if (final_line[0] == '\0')
        {
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

        i++;
    }
}
