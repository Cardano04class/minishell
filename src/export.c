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

t_env *sort_env(t_env *env_list) {
    t_env *sorted_list = NULL; // New list to hold sorted nodes
    t_env *current = env_list;
    t_env *new_node;

    // Create a copy of the original list into the sorted list
    while (current != NULL) {
        // Create a new node for the current environment variable
        new_node = (t_env *)malloc(sizeof(t_env));
        if (!new_node) {
            perror("Failed to allocate memory for new node");
            return NULL; // Handle allocation failure
        }
        
        new_node->key = ft_strdup(current->key);
        new_node->value = NULL; // Initialize value to NULL

        // If current node has a value, duplicate it
        if (current->value != NULL) {
            new_node->value = ft_strdup(current->value);
        }

        new_node->next = NULL;

        // Insert new_node into the sorted list in sorted order
        if (sorted_list == NULL || strcmp(sorted_list->key, new_node->key) > 0) {
            // Insert at the beginning
            new_node->next = sorted_list;
            sorted_list = new_node;
        } else {
            // Find the correct position to insert
            t_env *prev = sorted_list;
            while (prev->next != NULL && strcmp(prev->next->key, new_node->key) < 0) {
                prev = prev->next;
            }
            new_node->next = prev->next; // Link new node to the next node
            prev->next = new_node; // Link previous node to the new node
        }

        current = current->next; // Move to the next node in the original list
    }

    return sorted_list; // Return the new sorted list
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
    variables = NULL;
    if (args[1] == NULL)
    {
        variables = sort_env(*lst);   
        while(variables)
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
