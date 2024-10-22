/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/10/22 15:23:50 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return 1;
        i++;
    }    
    return 0;
}

void expand_var(t_env *env)
{
    int i = 0;
    while (g_mini.command->cmd[i])
    {
        if (has_dollar(g_mini.command->cmd[i]))
        {
            printf("entered\n");
            g_mini.command->cmd[i] = get_env(env, g_mini.command->cmd[i]);

        }    
        i++;
    }
}
