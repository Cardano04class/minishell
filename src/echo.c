/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/09/20 01:07:54 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(char **str)
{
    int flag = false;  
    int lock = false;  
    int i = 1;
    bool is_first_argument = true; 
    while (str[i])
    {
        if (is_first_argument && str[i][0] == '-' && str[i][1] != '\0')
        {
            int j = 1;
            bool all_n = true;
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
                lock = true;
                i++;
                continue;
            }
        }
        is_first_argument = false;
        int j = 0;
        while (str[i][j])
        {
            write(1, &str[i][j], 1); 
            j++;
        }
        if (str[i + 1])
            write(1, " ", 1);

        flag = true;
        i++;
    }
    if (!lock && flag)
        write(1, "\n", 1);
    return 0;
}

