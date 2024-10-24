/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/10/24 16:09:18 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int calc_var_len(t_env *env, char *line)
{
    char *value;
    int len;
    
    len = 0;
    value = get_env(env, line);
    while(value[len])
        len++;
    return len;
}

int len_trim(char *line)
{
    int i = 0;
    int original_len = 0;
    int in_var = 0;
    while(line[i])
    {
        if (line[i] == '$')
        {
            i++;
            in_var = 1;
            while (ft_isalnum(line[i]) && line[i])
                i++;
            i--;
        }
        else
            original_len++;
        i++;
    }
    return original_len;
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
    char *var_name;
    int var_pos;

    while (g_mini.command->cmd[i])
    {
        line = g_mini.command->cmd[i];
        var_pos = has_dollar(line);
        if (var_pos != -1)
        {
            var_name = extract_var_name(&line[var_pos + 1]);  
            if (var_name && var_exist(env, var_name))
            {
                char *var_value = get_env(env, var_name);  
                char *new = get_new_string(var_value, line); 
                g_mini.command->cmd[i] = new;  
                // printf("STR: %s\n", new);
                free(var_name);  
            }
        }
        i++;
    }
}
