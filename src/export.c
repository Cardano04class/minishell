/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/10/21 13:37:40 by mamir            ###   ########.fr       */
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

    while (current != NULL) 
    {
        t_env *new_node = (t_env *)malloc(sizeof(t_env));
        new_node->key = ft_strdup(current->key);
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

void update_env(t_env **env_list, char *name, char *value, bool plus_sign)
{
    t_env *current;

    current = *env_list;
    while (current)
    {
        if (plus_sign == true)
        {
            if (strcmp(current->key, name) == 0)
            {
                free(current->value);
                current->value = ft_strjoin(current->value, value);
                return;
            }
        }
        else
        {    
            if (strcmp(current->key, name) == 0)
            {
                free(current->value);
                current->value = ft_strdup(value);
                return;
            }
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
int find_plus(char *str)
{
    int i = 0;
    while(str[i])
    {
        if (str[i+1] == '=' && str[i] == '+')
            return i;
        i++;
    }
    return -1;
}

int find_equals(char *str)
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
    int plus_sign;
    equal_sign = find_equals(str);
    plus_sign = find_plus(str);
    var_value = NULL;
    if (equal_sign != -1)
    {
        var_name = ft_substr(str, 0, equal_sign);
        var_value = ft_substr(str, equal_sign + 1, ft_strlen(str) - equal_sign - 1);
        if (plus_sign != -1)
            var_name = ft_substr(str, 0, plus_sign);
        if (ft_strlen(var_value) == 0)
            var_value = ft_strdup("\"\"");
        if (!is_valid_name(var_name))
        {
            printf("export: '%s': not a valid identifier\n", var_name);
            return 1;
        }
        t_env *existing_node = env_exist(lst, var_name);
        if (existing_node)
        {
            if (plus_sign != -1)
                update_env(lst, var_name, var_value, true);
            else    
                update_env(lst, var_name, var_value, false);
        }
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
        var_name = ft_strdup(str);
        if (!is_valid_name(var_name))
        {
            printf("export: '%s': not a valid identifier\n", var_name);
            return 1;
        }
        t_env *existing_node = env_exist(lst, var_name);
        if (existing_node)
            return 0;
        else
        {
            if (!ft_export_node(lst, var_name, "")) 
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
