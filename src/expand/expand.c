/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/10/30 11:21:44 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variables(t_env *env, char *line)
{
    char *result = malloc(1024);
    if (!result) return NULL;
    int result_idx = 0;
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    int prev_quote = 0;

    while (line[i])
    {
        // Handle single quotes
        if (line[i] == '\'')
        {
            if (!in_double_quote)
            {
                if (!in_single_quote || !prev_quote)
                {
                    in_single_quote = !in_single_quote;
                }
            }
            prev_quote = (line[i] == '\'');
            result[result_idx++] = line[i++];
            continue;
        }

        // Handle double quotes
        if (line[i] == '\"')
        {
            if (!in_single_quote)
            {
                in_double_quote = !in_double_quote;
            }
            result[result_idx++] = line[i++];
            continue;
        }

        // Handle variables
        if (line[i] == '$' && !in_single_quote)
        {
            i++; // Skip $
            
            char var_name[100];
            int var_idx = 0;
            
            while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
            {
                var_name[var_idx++] = line[i++];
            }
            var_name[var_idx] = '\0';

            if (var_idx > 0)
            {
                char *var_value = get_env(env, var_name);
                if (var_value)
                {
                    strcpy(&result[result_idx], var_value);
                    result_idx += strlen(var_value);
                }
                continue;
            }
            continue;  // Skip lone $ if no valid variable
        }

        // Copy regular character
        result[result_idx++] = line[i++];
        prev_quote = 0;
    }

    result[result_idx] = '\0';
    return result;
}

int has_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return i;
        i++;
    }    
    return -1;
}

char *handle_quotes(char *str)
{
    if (!str)
        return NULL;

    char *result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;

    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (str[i])
    {
        // Detect and toggle quotes, skipping the empty quotes
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

        // Append character if it's not part of an empty quote
        result[j++] = str[i++];
    }

    result[j] = '\0';

    // Handle completely empty quotes case (like '' or "") by returning an empty string
    if (j == 0)
    {
        free(result);
        return strdup("");
    }

    return result;
}
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