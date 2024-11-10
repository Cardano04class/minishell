/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/11/06 23:00:16 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdbool.h>

int echo(char **str) {
    int i = 1;
    int j;
    bool flag = false;
    bool lock = false;
    bool all_n = false;
    bool is_first_argument = true;

    if (str[1] == NULL) {
        write(1, "\n", 1);
        return (0);
    }

    while (str[i]) {
        // Check if the first argument is -n (to avoid printing the newline)
        if (is_first_argument && str[i][0] == '-' && str[i][1] != '\0') {
            j = 1;
            all_n = true;
            while (str[i][j]) {
                if (str[i][j] != 'n') {
                    all_n = false;
                    break;
                }
                j++;
            }
            if (all_n) {
                lock = true; // Don't print the newline
                i++;
                continue;
            }
        }

        is_first_argument = false;

        // Print the content of the current argument, handling quotes if present
        j = 0;
        bool in_quotes = false;
        char quote_type = '\0';

        // Detect and handle quoted argument sections as a single argument
        while (str[i][j]) {
            // Toggle in_quotes mode when encountering a quote at the beginning or end
            if ((str[i][j] == '\'' || str[i][j] == '\"') && 
                (j == 0 || str[i][j + 1] == '\0')) {

                if (!in_quotes) {
                    in_quotes = true;
                    quote_type = str[i][j];
                } else if (in_quotes && str[i][j] == quote_type) {
                    in_quotes = false;
                }
                j++;
                continue;
            }

            // Print the character if it's not a quote or if we are inside quotes
            if (in_quotes || (str[i][j] != '\'' && str[i][j] != '\"')) {
                write(1, &str[i][j], 1);
            }

            j++;
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


