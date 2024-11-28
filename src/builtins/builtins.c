/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/11/28 15:01:55 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **list_to_array(t_list *list, t_env *env)
{
    size_t count = 0;
    t_list *temp = list;
    char **array;
    char *processed;
    char *merged;

    // First, count how many nodes are not empty strings
    while (temp)
    {
        if (strcmp(temp->content, "") != 0)  // Only count non-empty strings
            count++;
        temp = temp->next;
    }

    // Allocate memory for the array (with one extra space for NULL terminator)
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);

    count = 0;  // Reset count to reuse it for array filling

    // Now fill the array with processed content
    while (list)
    {
        if (strcmp(list->content, "") != 0)  // Skip empty nodes
        {
            if (strchr(list->content, '=') && list->next && list->next->content[0] == '"')
            {
                // If the current node is a variable assignment (a=) and the next node is a quoted value ("ls")
                processed = expand_variables(env, list->next->content);
                char *value = remove_quotes(processed);
                free(processed);

                merged = merge_args(list->content, value);
                free(value);

                array[count++] = merged;  // Add the merged variable to the array

                // Skip the next node (value node)
                list = list->next;
            }
            else
            {
                // Regular node processing
                processed = expand_variables(env, list->content);
                if (processed)
                {
                    char *final = remove_quotes(processed);
                    free(processed);
                    array[count++] = final;  // Add the processed content to the array
                }
                else
                {
                    array[count++] = strdup(list->content);  // Fallback to original content
                }
            }
        }
        list = list->next;
    }

    array[count] = NULL;  // Null-terminate the array
    return (array);
}



int run_builtins(t_env **env, t_list *list)
{
    char **arg;

    arg = list_to_array(list, *env);
    if (!arg || !arg[0])
    {
        free(arg);
        return (0);
    }
    if (strcmp(arg[0], "export") == 0)
        export(arg, env);
    else if (strncmp("env", arg[0], 4) == 0)
        print_env(*env);
    else if (strcmp("pwd", arg[0]) == 0)
        pwd(env);
    else if (strcmp("echo", arg[0]) == 0)
        echo(arg);
    else if (strcmp(arg[0], "cd") == 0)
        cd(env, arg);
    else if (strcmp(arg[0], "unset") == 0)
        unset(arg, env);
    else if (strcmp(arg[0], "exit") == 0)
    {
        free(arg);
        exit(0);
    }
    else
    {
        free(arg);
        return (0);
    }
	size_t i = 0;
    while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
    return (1);
}

