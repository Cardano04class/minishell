/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/11/13 11:00:57 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(char **str)
{
    int i = 1;
    int j;
    bool n_option = false;

    // If no arguments, just print newline and return
    if (str[1] == NULL)
    {
        write(1, "\n", 1);
        return (0);
    }
    // Process -n options
    while (str[i] && str[i][0] == '-' && str[i][1] == 'n')
    {
        j = 2;
        while (str[i][j] == 'n')
            j++;
        if (str[i][j] == '\0')  // Only if the argument is all 'n's
        {
            n_option = true;
            i++;
        }
        else
            break;
    }
    // Print arguments
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            write(1, &str[i][j], 1);
            j++;
        }
        if (str[i + 1])  // Print space only if not the last argument
            write(1, " ", 1);
        i++;
    }

    // Print newline if -n was not specified
    if (!n_option)
        write(1, "\n", 1);

    return (0);
}



