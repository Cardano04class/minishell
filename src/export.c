/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/09/30 02:46:13 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int set_env(t_env **lst, char *str)
{
    t_env *node;
    char *var_name;
    char *var_value;
    int equal_sign;
    char *value;
    
    equal_sign = find_equals(str);
    if (equal_sign != -1)
    {
        var_name = ft_substr(str, 0, equal_sign);
        var_value = ft_substr(str, equal_sign + 1, ft_strlen(str) - equal_sign - 1);
        if (!is_valid_name(var_name))
        {
            printf("invalid var_name: %s\n", var_name);
        }
        node = ft_env_new(var_name, var_value);
        if (node)
            ft_env_addback(lst, node);
        else
            perror("Error setting variable:");
    }
    else
    {
        value = getenv(str);
        if (value != NULL)
            printf("%s=%s\n", str, value);
        else
            printf("%s: not found\n", str);
    }
    return 0;
}

int export(char **args, char **env, t_env **lst)
{
    
    int i;
    
    
    if (args[1] == NULL)
    {
        ft_env(env);
        return 1;
    }
    i = 1;
    while (args[i])
    {
        set_env(lst, args[i]);
        i++;
    }
    return 0;
}
