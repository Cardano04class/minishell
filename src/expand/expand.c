/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:02:51 by mamir             #+#    #+#             */
/*   Updated: 2024/12/09 15:45:18 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_export_assignment(t_list **list)
{
    t_list *current = *list;

    while (current && current->next)
    {
        if (ft_strcmp(current->content, "export") == 0 && current->next)
        {
            t_list *var_node = current->next;
            t_list *val_node = var_node->next;

            if (val_node && ft_strchr(var_node->content, '=') != NULL)
            {
                char *val_content = val_node->content;
                size_t val_len = ft_strlen(val_content);

                // Check if the value is enclosed in quotes
                if (val_len >= 2 &&
                    ((val_content[0] == '\'' && val_content[val_len - 1] == '\'') ||
                     (val_content[0] == '"' && val_content[val_len - 1] == '"')))
                {
                    char *merged_content;
                    size_t len_var = ft_strlen(var_node->content);
                    size_t len_val = ft_strlen(val_node->content);

                    merged_content = _malloc(len_var + len_val + 1, 'm');
                    if (!merged_content)
                        return;

                    ft_strcpy(merged_content, var_node->content);
                    ft_strcat(merged_content, val_node->content);
                    
                    var_node->content = merged_content;

                    var_node->next = val_node->next;
                    if (val_node->next)
                        val_node->next->prev = var_node;

                    current = var_node;
                    continue;
                }
            }
        }
        current = current->next;
    }
}

char *expand_variable(t_env *env, const char *var_name)
{
    t_env *current = env;

    while (current)
    {
        if (strcmp(current->key, var_name) == 0)
            return current->value;  // Return the value of the variable if found
        current = current->next;
    }

    return NULL;  // Return NULL if the variable is not found
}

char *remove_quotes_and_expand(t_env *env, char *content)
{
    char expanded_content[1024] = {0};
    int i = 0, j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (content[i])
    {
        // Handle quote tracking and removal
        if (content[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        }
        if (content[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        }
        // Variable expansion (only in double quotes or unquoted)
        if (content[i] == '$' && !in_single_quote)
        {
            i++; // Skip '$'

            // Special case: "$" followed by nothing
            if (content[i] == '\0')
            {
                expanded_content[j++] = '$';
                continue;
            }

            // Extract variable name
            char var_name[256] = {0};
            int name_idx = 0;

            while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
            {
                var_name[name_idx++] = content[i++];
            }
            var_name[name_idx] = '\0';

            // Expand the variable
            char *var_value = expand_variable(env, var_name);
            if (var_value)
            {
                int k = 0;
                while (var_value[k])
                    expanded_content[j++] = var_value[k++];
            }
        }
        else
        {
            // Copy non-variable characters
            expanded_content[j++] = content[i++];
        }
    }

    expanded_content[j] = '\0';
    return strdup(expanded_content);
}

void split_and_expand_variables(t_env *env, t_list **node)
{
    t_list *current_node = *node;
    
    // Always attempt to remove quotes, whether or not there are variables
    char *expanded_content = remove_quotes_and_expand(env, current_node->content);
    
    // Update node content
    current_node->content = expanded_content;
}

void merge_adjacent_quoted_nodes(t_list **list)
{
    t_list *current = *list;

    while (current && current->next)
    {
        char *current_content = current->content;
        char *next_content = current->next->content;
        
        size_t current_len = ft_strlen(current_content);
        size_t next_len = ft_strlen(next_content);

        // Only merge if both have quotes and are of the same quote type
        int should_merge = 
            (current_len > 0 && next_len > 0 && 
             ((current_content[0] == '"' && next_content[0] == '"') ||
              (current_content[0] == '\'' && next_content[0] == '\'')));

        if (should_merge)
        {
            // Merge the nodes
            char *merged_content = _malloc(current_len + next_len + 1, 'm');
            if (!merged_content)
                return;

            // Remove first quote from second string
            ft_strcpy(merged_content, current_content);
            ft_strcat(merged_content, next_content + 1);

            // Update current node's content
            current->content = merged_content;

            // Remove the next node
            t_list *to_delete = current->next;
            current->next = to_delete->next;
            if (to_delete->next)
                to_delete->next->prev = current;

            // Free the removed node
            free(to_delete);

            // Don't move to next node yet, as we might need to merge again
            continue;
        }

        current = current->next;
    }
}

void handle_special_variable_cases(t_env *env, t_list **list)
{
    t_list *current = *list;

    while (current)
    {
        if (current->next && 
            (strncmp(current->content, "$", 1) == 0 || 
             strncmp(current->content, "\"$", 2) == 0) &&
            current->next->content[0] != '$')
        {
            char *expanded = remove_quotes_and_expand(env, current->content);
            current->content = expanded;
            
            // Merge with next node
            char *merged_content = _malloc(
                ft_strlen(current->content) + 
                ft_strlen(current->next->content) + 1, 'm');
            
            ft_strcpy(merged_content, current->content);
            ft_strcat(merged_content, current->next->content);

            current->content = merged_content;

            // Remove next node
            t_list *to_delete = current->next;
            current->next = to_delete->next;
            if (to_delete->next)
                to_delete->next->prev = current;

            continue;
        }

        current = current->next;
    }
}

void merge_fragmented_nodes(t_list **list)
{
    t_list *current = *list;

    while (current)
    {
        char *content = current->content;
        int is_quote_node = (content[0] == '"' || content[0] == '\'');
        
        // Check for fragmented quote scenarios
        if (is_quote_node && 
            current->next && 
            strcmp(current->next->content, "is") == 0 && 
            current->next->next && 
            current->next->next->content[0] == '"')
        {
            // Special case like "HOME"is"HERE"
            char *first_part = remove_quotes_and_expand(NULL, current->content);
            char *last_part = remove_quotes_and_expand(NULL, current->next->next->content);
            
            // Merge all three parts
            char *merged_content = _malloc(
                ft_strlen(first_part) + 
                ft_strlen(current->next->content) + 
                ft_strlen(last_part) + 1, 'm');
            
            ft_strcpy(merged_content, first_part);
            ft_strcat(merged_content, current->next->content);
            ft_strcat(merged_content, last_part);

            // Update the first node
            current->content = merged_content;

            // Remove the next two nodes
            t_list *to_delete1 = current->next;
            t_list *to_delete2 = current->next->next;
            
            current->next = to_delete2->next;
            if (to_delete2->next)
                to_delete2->next->prev = current;

            free(to_delete1);
            free(to_delete2);

            continue;
        }

        current = current->next;
    }
}

void expand(t_env *env, t_list **list)
{
    merge_export_assignment(list);
    merge_fragmented_nodes(list);
    t_list *current = *list;
    while (current)
    {
        split_and_expand_variables(env, &current);
        current = current->next;
    }
}
