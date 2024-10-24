/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/10/23 10:20:39 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int var_exist(t_env *env, char *line)
{
    if (get_env(env, line) != NULL)
        return 1;
    return 0;
}

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

int has_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return 1;
        i++;
    }    
    return 0;
}

void expand(t_env *env)
{
    int i = 0;
    char *line;

    
    while (g_mini.command->cmd[i])
    {
        line = g_mini.command->cmd[i];
        if (has_dollar(line))
        {
            if (var_exist(env,line))
            {
               printf("kayna\n");
            }
        }
        i++;
        free(line);
    }
}
