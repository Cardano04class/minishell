/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/04 18:00:05 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **list_to_array(t_list *list)
{
    size_t count = 0;
    size_t i = 0;
    t_list *temp = list;
    char **array;
    char **split;

    // First, count the nodes in the linked list
    while (temp)
    {
        if (temp->content && temp->content[0] != '\0')  // Skip empty content
            count++;
        temp = temp->next;
    }

    // Allocate memory for the array (with one extra space for NULL terminator)
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return NULL;

    temp = list;
    // Populate the array with valid content
    while (temp)
    {
        if (temp->content && temp->content[0] != '\0')  // Skip empty content
        {
            // If the content contains spaces, split it
            if (strchr(temp->content, ' '))
            {
                split = ft_split(temp->content, ' ');
                if (!split)
                {
                    free(array);
                    return NULL;
                }

                size_t j = 0;
                while (split[j])
                {
                    array[i] = strdup(split[j]);
                    if (!array[i])
                    {
                        free_array(array);
                        free_array(split);
                        return NULL;
                    }
                    i++;
                    j++;
                }
                free_array(split);  // Free the split parts
            }
            else
            {
                // Directly copy the content if no spaces are found
                array[i] = strdup(temp->content);
                if (!array[i])
                {
                    free_array(array);
                    return NULL;
                }
                i++;
            }
        }
        temp = temp->next;
    }

    // Null-terminate the array
    array[i] = NULL;

    return array;
}

void split_args(char ***array, size_t *count)
{
    char **new_array;
    size_t new_count = 0;
    size_t i;
    char *token;
    char *start;
    char *end;
    int in_quote;

    // First, count total potential tokens
    i = 0;
    while ((*array)[i])
    {
        token = (*array)[i];
        start = token;
        in_quote = 0;

        while (*token)
        {
            if (*token == '"' || *token == '\'')
                in_quote = !in_quote;

            if (*token == ' ' && !in_quote)
                new_count++;
            token++;
        }
        new_count++;
        i++;
    }

    // Allocate new array
    new_array = malloc(sizeof(char *) * (new_count + 1));
    if (!new_array)
        return;

    // Fill the new array with split tokens
    new_count = 0;
    i = 0;
    while ((*array)[i])
    {
        start = (*array)[i];
        in_quote = 0;
        while (*start)
        {
            end = start;

            // Find the end of the token (while space is outside quotes)
            while (*end && (*end != ' ' || in_quote))
            {
                if (*end == '"' || *end == '\'')
                    in_quote = !in_quote;
                end++;
            }

            // Allocate and copy the token
            size_t len = end - start;
            new_array[new_count] = malloc(len + 1);
            if (!new_array[new_count])
            {
                free_array(new_array);
                return;
            }
            size_t j = 0;
            while (j < len)
            {
                new_array[new_count][j] = start[j];
                j++;
            }
            new_array[new_count][j] = '\0';

            new_count++;

            // Move to the next token
            start = (*end) ? end + 1 : end;
        }
        i++;
    }

    new_array[new_count] = NULL;

    // Free original array
    i = 0;
    while ((*array)[i])
    {
        free((*array)[i]);
        i++;
    }
    free(*array);

    *array = new_array;
    *count = new_count;
}


int run_builtins(t_env **env, t_list *list)
{
    char **arg;
    size_t count;


    arg = list_to_array(list);
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