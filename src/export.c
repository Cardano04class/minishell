/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/09/30 01:48:49 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_env(char *name, char *value, int overwrite)
{

}

int is_valid_name(char *str)
{
    int i = 0;

    if (!ft_isalpha(str[i]) && str[i] != '_')
        return 0;
    i++;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

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
    char *value;
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
            if (!is_valid_name(var_name))
            {
                printf("invalid var_name: %s\n", var_name);
                continue;
            }
            set_env()
        }
        else
        {
            value = getenv(args[i]);
            if (value != NULL)
                printf("%s=%s\n", args[i], value);
            else
                printf("%s: not found\n", args[i]);
        }
        i++;
    }
    return 0;
}
