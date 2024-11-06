/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/11/06 17:13:32 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdbool.h>

int echo(char **str)
{
    int i = 1;
    int j = 0;
    bool flag = false;
    bool lock = false;
    bool all_n = false;
    bool is_first_argument = true;

    if (str[1] == NULL)
    {
        write(1, "\n", 1);
        return (0);
    }

    while (str[i])
    {
        // Check if the first argument is -n (to avoid printing the newline)
        if (is_first_argument && str[i][0] == '-' && str[i][1] != '\0')
        {
            j = 1;
            all_n = true;
            while (str[i][j])
            {
                if (str[i][j] != 'n')
                {
                    all_n = false;
                    break;
                }
                j++;
            }
            if (all_n)
            {
                lock = true; // Don't print the newline
                i++;
                continue;
            }
        }

        is_first_argument = false;

        // If the argument starts with a quote, handle quoted content
        if (str[i][0] == '\'' || str[i][0] == '\"')
        {
            char quote = str[i][0]; // Store the quote type
            write(1, &quote, 1);    // Print the opening quote

            // Skip the first quote
            j = 1;
            while (str[i][j] && str[i][j] != quote) 
            {
                write(1, &str[i][j], 1); // Print the content inside the quotes
                j++;
            }

            write(1, &quote, 1); // Print the closing quote
        }
        else 
        {
            // Otherwise, print the content without modification
            j = 0;
            while (str[i][j])
            {
                write(1, &str[i][j], 1);
                j++;
            }
        }

        // Print a space between arguments, but not after the last one
        if (str[i + 1])
            write(1, " ", 1);

        flag = true;
        i++;
    }

    // Print the newline if the -n option was not provided
    if (!lock && flag)
        write(1, "\n", 1);

    return (0);
}

