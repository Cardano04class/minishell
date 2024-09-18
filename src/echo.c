/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/09/17 17:08:17 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(char **str)
{
    int flag = false;
    int lock = false;
    int i = 0;

    while (str[i])
    {
        if (str[i][0] == '-' && !lock)
        {
            int j = 1;
            while (str[i][j])
            {
                if (str[i][j] != 'n')
                {
                    lock = false;
                    break;
                }
                j++;
            }
        }
        else
        {
            int j = 0;
            while (str[i][j])
            {
                write(1, &str[i][j], 1);
                j++;
            }
            if (str[i + 1]) 
                write(1, " ", 1);
            flag = true;
        }
        i++;
    }
    if (lock && !flag)
        write(1, "\n", 1);
    
    return 0;
}
