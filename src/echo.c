/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/09/17 15:55:46 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool has_n_flag(char *str, int *i) {
    int j = *i;
    
    while (str[j] == ' ')
        j++;
    if (str[j] == '-' && str[j + 1] == 'n' && (str[j + 2] == ' ' || str[j + 2] == '\0')) 
    {
        j += 2;
        while (str[j] == ' ')
            j++;
        *i = j;
        return true;
    }
    return false;
}

void echo(t_list **list, char *str) 
{
    int i = 4;  
    bool newline = true;

    (void)list;  
    if (strncmp(str, "echo", 4) == 0) 
    {
        if (str[i] == '\0') 
        {
            write(1, "\n", 1);
            return;
        }
        while (str[i] == ' ')
            i++;
        if (has_n_flag(str, &i)) 
            newline = false;  
        while (str[i] == ' ')
            i++;
        if (str[i] == '\0') 
        {
            if (newline)
                write(1, "\n", 1);
            return;
        }
        while (str[i]) 
        {
            write(1, &str[i], 1);
            i++;
        }
        if (newline)
            write(1, "\n", 1);
    }
}
