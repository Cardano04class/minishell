/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/10/08 04:22:49 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int already_sorted(t_env *lst)
{
    while (lst)
    {
        if (strcmp(lst->key,lst->next->key) > 0 )
            return 1;
        if (strcmp(lst->key,lst->next->key) < 0 )
            return 1;
        lst = lst->next;
    }
    return 0;
}

t_env *sort_env(t_env **env_list) {
    t_env *current;
    t_env *next_node;
    char *tmp_key;
    char *tmp_value;
    int swapped;

    if (env_list == NULL || (*env_list)->next == NULL)
        return NULL;
    swapped = 1;
    while (swapped) 
    {
        swapped = 0;
        current = *env_list;
        while (current->next != NULL) 
        {
            next_node = current->next;
            if (strcmp(current->key, next_node->key) > 0) 
            {
                tmp_key = ft_strdup(current->key);
                if (current->value == NULL)
                    tmp_value = NULL;
                else
                    tmp_value = ft_strdup(current->value);
                free(current->key);
                free(current->value);
                current->key = next_node->key;
                current->value = next_node->value;
                next_node->key = tmp_key;
                next_node->value = tmp_value;
                swapped = 1;
            }
            current = next_node;
        }
    }
    return *env_list;
}

int env_exist(t_env **env_list, char *name)
{
    t_env *current;

    current = *env_list;
    while (current)
    {
        if (strcmp(current->key, name) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}

void update_env(t_env **env_list, char *name, char *value)
{
    t_env *current;

    current = *env_list;
    while (current)
    {
        if (strcmp(current->key, name) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
}

t_env *ft_export_node(t_env **env_lst, char *name, char *value) 
{
    t_env *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node) 
    {
        perror("Failed to allocate memory for new environment node");
        return NULL;
    }
    new_node->key = ft_strdup(name);
    if (!new_node->key) 
    {
        perror("Failed to allocate memory for variable name");
        free(new_node);
        return NULL;
    }
    if (value) 
    {
        new_node->value = ft_strdup(value);
        if (!new_node->value) 
        {
            perror("Failed to allocate memory for variable value");
            free(new_node->key);
            free(new_node);
            return NULL;
        }
    }
    else 
        new_node->value = NULL;
    new_node->next = NULL;
    if (*env_lst == NULL)
        *env_lst = new_node;
    else 
    {
        t_env *current = *env_lst;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    return new_node;  
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
        if (env_exist(lst, var_name))
            update_env(lst, var_name, var_value);
        else
        {
            if (!ft_export_node(lst, var_name, var_value)) 
            {
                perror("Error setting variable:");
                free(var_name);
                free(var_value);
                return 1;
            }
        }
        free(var_name);
        free(var_value);
    }
    else
    {
        if(ft_export_node(lst, str, NULL) == 0)
        {
            perror("failed adding varible\n");
            return 1;
        }
    }
    return 0;
}

int export(char **args, t_env **lst)
{
    int i;
    t_env *variables;

    variables = *lst;
    if (args[1] == NULL)
    {
        if (!already_sorted(*lst))
        {
            variables = sort_env(lst);
        }
        while (variables)
	    {
            if (variables->value == NULL)
                printf("declare -x %s\n", variables->key);
		    else
                printf("declare -x %s=%s\n", variables->key, variables->value);
		    variables = variables->next;
	    }
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
