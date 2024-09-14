/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/09/15 00:36:57 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool has_n_flag(char *str, int *i) {
    int j = *i;
    
    // Skip any leading spaces
    while (str[j] == ' ')
        j++;

    // Check if "-n" is present after skipping spaces
    if (str[j] == '-' && str[j + 1] == 'n' && (str[j + 2] == ' ' || str[j + 2] == '\0')) {
        // Move index past "-n" and any following spaces
        j += 2;
        while (str[j] == ' ')
            j++;
        *i = j;
        return true;
    }

    return false;
}

void echo(t_list **list, char *str) {
    int i = 4;  // Start after "echo"
    bool newline = true;

    (void)list;  // Unused parameter to avoid warnings

    // Check if the command starts with "echo"
    if (strncmp(str, "echo", 4) == 0) {
        // Ensure there is something after "echo"
        if (str[i] == '\0') {
            // Just "echo" without any additional text, print a newline
            write(1, "\n", 1);
            return;
        }

        // Skip any spaces after "echo"
        while (str[i] == ' ')
            i++;

        // Check for the "-n" flag
        if (has_n_flag(str, &i)) {
            newline = false;  // Suppress newline if "-n" is found
        }

        // Skip leading spaces after possible "-n" flag
        while (str[i] == ' ')
            i++;

        // If there is still no content after "echo" or "-n", return without printing anything
        if (str[i] == '\0') {
            if (newline)
                write(1, "\n", 1);
            return;
        }

        // Print the rest of the string
        while (str[i]) {
            write(1, &str[i], 1);
            i++;
        }

        // Add newline if the "-n" flag was not provided
        if (newline)
            write(1, "\n", 1);
    }
}