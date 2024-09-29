/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/09/30 00:36:13 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char find_equals(char *str)
{
    int i = 0;
    while(str[i])
    {
        if (str[i] == '=')
            return i;
        i++;
    }
    return -1;
}

int export(char **args, char **env)
{
    int i;
    int equal_sign = 0;
    char *var_name;
    char *var_value;
    
    if (args[1] == NULL)
    {
        ft_env(env);
        return 1;
    }
    i = 1;
    while (args[i])
    {
        equal_sign = find_equals(args[i]);
        if (equal_sign != -1)
        {
            var_name = ft_substr(args[i], 0, equal_sign);
            var_value = ft_substr(args[i], equal_sign + 1, ft_strlen(args[i]) - equal_sign - 1);
            printf("name: %s\nvalue: %s\n", var_name, var_value);
        }
        i++;
    }
    return 0;
}
