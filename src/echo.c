/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/09/15 00:31:46 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo(t_list **list, char *str)
{
    int i;

    (void)list;
    if (strncmp(str, "echo", 4) == 0)
    {
        i = 5;
        if (str[i] == '-' && str[i+1] == 'n')
        {
            i += 3;
            while (str[i])
            {
                write(1, &str[i], 1);
                i++;
            }             
        }
        else
        {
            while (str[i])
            {
                write(1, &str[i], 1);
                i++;
            }
            write(1, "\n", 1);
        }
    }
}