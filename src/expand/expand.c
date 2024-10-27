/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/10/27 23:28:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variables(t_env *env, char *line)
{
    char *result = malloc(1024);  // Initial result buffer
    if (!result) return NULL;
    int result_idx = 0;

    int in_single_quote = 0, in_double_quote = 0;
    int line_idx = 0;

    while (line[line_idx])
    {
        if (line[line_idx] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;  // Toggle single-quote mode
            result[result_idx++] = line[line_idx++];  // Copy quote as-is
            continue;
        }
        else if (line[line_idx] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;  // Toggle double-quote mode
            result[result_idx++] = line[line_idx++];  // Copy quote as-is
            continue;
        }

        if (line[line_idx] == '$' && !in_single_quote)  // Expand only if not in single quotes
        {
            line_idx++;  // Move past '$'

            // Check for $" syntax (localized string) and handle as plain text
            if (line[line_idx] == '\"')
            {
                line_idx++;  // Skip past the double-quote after $

                // Copy everything inside $"..." as-is
                while (line[line_idx] && line[line_idx] != '\"')
                {
                    result[result_idx++] = line[line_idx++];
                }
                if (line[line_idx] == '\"')  // Skip the closing quote if it exists
                    line_idx++;
                continue;
            }

            char var_name[100];
            int var_name_idx = 0;

            // Extract variable name
            while (isalnum(line[line_idx]) || line[line_idx] == '_')
            {
                var_name[var_name_idx++] = line[line_idx++];
            }
            var_name[var_name_idx] = '\0';

            if (var_name_idx == 0)  // No valid variable name found
            {
                result[result_idx++] = '$';  // Keep the `$` as-is
            }
            else
            {
                // Lookup environment variable
                char *var_value = get_env(env, var_name);
                if (var_value)
                {
                    strcpy(&result[result_idx], var_value);  // Copy variable value into result
                    result_idx += strlen(var_value);
                }
            }
        }
        else
        {
            // Copy character as-is
            result[result_idx++] = line[line_idx++];
        }
    }
    result[result_idx] = '\0';  // Null-terminate the result string
    return result;
}

char *get_new_string(char *var_value, char *line)
{
    char *result;
    int i;
    int new_len;
    int line_idx;
    int result_idx;

    new_len = ft_strlen(line)+ ft_strlen(var_value);
    result = malloc(new_len + 1);
    if (!result)
        return NULL;
    line_idx = 0;
    result_idx = 0;
    while (line[line_idx])
    {
        if (line[line_idx] == '$')
        {
            line_idx++;
            while (ft_isalnum(line[line_idx]) && line[line_idx])
                line_idx++;
            i = 0;
            while(var_value[i])
            {
                result[result_idx] = var_value[i];
                i++;
                result_idx++;
            }
        }
        else
        {
            result[result_idx] = line[line_idx];
            line_idx++;
            result_idx++;
        }
    }
    result[result_idx] = '\0';
    return result;
}

char *extract_var_name(char *line)
{
    int i = 0;
    
    if (!line[i] || !ft_isalnum(line[i]))  
        return NULL;
    while (line[i] && ft_isalnum(line[i])) 
        i++;
    char *var_name = malloc(i + 1);
    if (!var_name)
        return NULL; 
    int j = 0; 
    while (j < i)
    {
        var_name[j] = line[j];
        j++;
    }
    var_name[i] = '\0';  
    return var_name;
}

int var_exist(t_env *env, char *line)
{
    return get_env(env, line) != NULL;
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

void expand(t_env *env)
{
    int i = 0;
    char *line;
    char *expanded_line;

    while (g_mini.command->cmd[i])
    {
        line = g_mini.command->cmd[i];
        expanded_line = expand_variables(env, line);
        if (expanded_line)
        {
            free(g_mini.command->cmd[i]);
            g_mini.command->cmd[i] = expanded_line;
        }
        i++;
    }
}
