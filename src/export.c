/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/10/07 23:58:55 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_exists(t_env **env_list, char *name, char *value)
{
    t_env *current;

    current = *env_list;
    while (current)
    {
        if (strcmp(current->key, name) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

t_env *ft_export_node(t_env **env_lst, char *name, char *value)
{
    t_env *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node) {
        perror("Failed to allocate memory for new environment node");
        return NULL;
    }

    new_node->key = ft_strdup(name);
    new_node->value = strdup(value);
    new_node->next = NULL;

    if (!new_node->key || !new_node->value) {
        perror("Failed to allocate memory for variable name or value");
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return NULL;
    }
    if (*env_lst == NULL) {
        *env_lst = new_node;  // Set as head if list is empty
    } else {
        t_env *current = *env_lst;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    return new_node;  
}

void print_value(char *str, t_env *env_list)
{
    t_env *current;

    current = env_list;
    while(current)
    {
        if (strcmp(current->key, str) == 0)
        {
            printf("%s=%s\n", current->key, current->value);
            return;
        }
        current = current->next;
    }
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

int set_env(t_env **lst, char *str)
{
    char *var_name;
    char *var_value;
    int equal_sign;
    
    equal_sign = find_equals(str);
    if (equal_sign != -1)
    {
        var_name = ft_substr(str, 0, equal_sign);
        var_value = ft_substr(str, equal_sign + 1, ft_strlen(str) - equal_sign - 1);
        if (!is_valid_name(var_name))
        {
            printf("invalid var_name: %s\n", var_name);
            return 1;
        }
        if (!env_exists(lst, var_name, var_value))
        {
            if (!ft_export_node(lst, var_name, var_value)) 
            {
                perror("Error setting variable:");
                return 1;
            }
        }
        free(var_name);
        free(var_value);
    }
    else
        print_value(str, *lst);
    return 0;
}

int export(char **args, t_env **lst)
{
    int i;
    
    if (args[1] == NULL)
    {
        // sort_env(*lst);
        print_env(*lst);
        return 0;
    }
    i = 1;
    while (args[i])
    {
        set_env(lst,args[i]);
        i++;
    }
    return 0;
}
