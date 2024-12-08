/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/12/07 18:03:45 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_n_option(char *str)
{
    int j;

    if (str[0] != '-' || str[1] != 'n')
        return (false);
    j = 2;
    while (str[j] == 'n')
        j++;
    if (str[j] == '\0')
        return (true);
    return (false);
}

int print_arguments(char **str, int i)
{
    int j;

    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            write(1, &str[i][j], 1);  // Print each character of the current argument
            j++;
        }
        // Only print a space if there is another argument
        if (str[i + 1])
            write(1, " ", 1);
        i++;
    }
    return (i);
}

int echo(char **args)
{
    int i;
    bool n_option;

    i = 1;
    n_option = false;
    dprintf(2, "ana echo\n");
    while (args[i])
    {
        while (args[i] && is_n_option(args[i]))
        {
            n_option = true;
            i++;
        }
        print_arguments(args, i);
        if (!n_option)
            write(1, "\n", 1);
        i++;
    }
    return (0);
}
