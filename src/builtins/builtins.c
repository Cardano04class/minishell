/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/03 12:34:38 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **list_to_array(t_list *list, t_env *env)
{
    size_t count = 0;
    t_list *temp = list;
    char **array;

    // First, expand variables in the list
    while (temp)
    {
        if (temp->content && temp->content[0] == '$')
        {
            char *expanded = expand_variables(env, temp->content);
            if (expanded)
            {
                free(temp->content);
                temp->content = expanded;
            }
        }
        count++;
        temp = temp->next;
    }

    // Allocate memory for the array (with one extra space for NULL terminator)
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return (NULL);

    count = 0;
    while (list)
    {
        array[count++] = strdup(list->content);
        list = list->next;
    }
    array[count] = NULL; // Null-terminate the array
    return (array);
}



void split_args(char ***array, size_t *count)
{
    char **new_array;
    size_t new_count = 0;
    size_t i, j;
    char *token;

    // First, count total potential tokens
    for (i = 0; (*array)[i]; i++)
    {
        token = (*array)[i];
        for (j = 0; token[j]; j++)
        {
            if (token[j] == ' ')
                new_count++;
        }
        new_count++;
    }

    // Allocate new array
    new_array = malloc(sizeof(char *) * (new_count + 1));
    if (!new_array)
        return;

    new_count = 0;
    for (i = 0; (*array)[i]; i++)
    {
        token = (*array)[i];
        // If no spaces, just copy the original token
        if (!strchr(token, ' '))
        {
            new_array[new_count++] = strdup(token);
            continue;
        }

        // Split by spaces
        char *start = token;
        for (j = 0; token[j]; j++)
        {
            if (token[j] == ' ')
            {
                // Found a space, terminate and add token
                token[j] = '\0';
                new_array[new_count++] = strdup(start);
                
                // Move to next token start
                start = &token[j + 1];
            }
        }

        // Add last token
        if (start != token + j)
            new_array[new_count++] = strdup(start);
    }

    new_array[new_count] = NULL;

    // Free original array
    for (i = 0; (*array)[i]; i++)
        free((*array)[i]);
    free(*array);

    // Update array and count
    *array = new_array;
    *count = new_count;
}

int run_builtins(t_env **env, t_list *list)
{
    char **arg;
    size_t count;

    arg = list_to_array(list, *env);
    if (!arg || !arg[0])
    {
        free(arg);
        return (0);
    }

    // Split arguments for expanded variables
    count = 0;
    while (arg[count])
        count++; 
    split_args(&arg, &count);
    // if (strcmp(arg[0], "exit") == 0)
    //     exit_shell();
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
        free_array(arg);
        exit(0);
    }
    else
    {
        free_array(arg);
        return (0);
    }

    free_array(arg);
    return (1);
}