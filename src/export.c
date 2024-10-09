/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/10/09 05:34:29 by mamir            ###   ########.fr       */
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

t_env *sort_env(const t_env *env_list) 
{
    t_env *sorted_list = NULL;
    const t_env *current = env_list;

    // Create a copy of the original list into the sorted list
    while (current != NULL) 
    {
        t_env *new_node = (t_env *)malloc(sizeof(t_env));
        new_node->key = ft_strdup(current->key);
        
        // Allocate memory for value only if it is not NULL
        if (current->value != NULL) 
            new_node->value = ft_strdup(current->value);
        else 
            new_node->value = NULL;
        new_node->next = NULL;

        // Insert new_node into the sorted list in sorted order
        if (sorted_list == NULL || strcmp(sorted_list->key, new_node->key) > 0) 
        {
            new_node->next = sorted_list;
            sorted_list = new_node;
        } 
        else 
        {
            t_env *prev = sorted_list;
            while (prev->next != NULL && strcmp(prev->next->key, new_node->key) < 0) 
            {
                prev = prev->next;
            }
            new_node->next = prev->next;
            prev->next = new_node;
        }
        current = current->next;
    }
    return sorted_list; 
}

t_env *env_exist(t_env **env_list, const char *name)
{
    t_env *current = *env_list;

    while (current)
    {
        if (strcmp(current->key, name) == 0)
            return current; 
        current = current->next;
    }
    return NULL;
}

void update_env(t_env **env_list, char *name, char *value)
{
    t_env *current;

    current = *env_list;
    while (current)
    {
        if (strcmp(current->key, name) == 0)
        {
            (*env_list)->is_exported = true;
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
        new_node->value = ft_strdup("''");
    new_node->is_exported = true;
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
            free(var_name);
            free(var_value);
            return 1;
        }

        // Check if the variable already exists
        t_env *existing_node = env_exist(lst, var_name);
        if (existing_node)
        {
            // Update the variable's value
            update_env(lst, var_name, var_value);
        }
        else
        {
            // Create a new environment node
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
        // Handle the case where there is no '='
        var_name = ft_strdup(str); // Duplicate the variable name
        if (!is_valid_name(var_name))
        {
            printf("invalid var_name: %s\n", var_name);
            free(var_name);
            return 1;
        }

        // Check if the variable exists; if it does, update it to an empty string
        t_env *existing_node = env_exist(lst, var_name);
        if (existing_node)
        {
            update_env(lst, var_name, ""); // Update to empty string
        }
        else
        {
            // Create a new environment node with an empty value
            if (!ft_export_node(lst, var_name, NULL)) 
            {
                perror("failed adding variable\n");
                free(var_name);
                return 1;
            }
        }

        free(var_name);
    }
    return 0;
}


int export(char **args, t_env **lst)
{
    int i;
    t_env *sorted;

    sorted = NULL;
    if (args[1] == NULL)
    {
        sorted = sort_env(*lst);
        print_export(sorted);
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
