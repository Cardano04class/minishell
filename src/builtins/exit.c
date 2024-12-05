/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:07:23 by mamir             #+#    #+#             */
/*   Updated: 2024/12/05 18:23:13 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_shell(t_cmd *arg)
{
    int i = 1;
    if(arg->cmd[i] == NULL)
    {
        printf("exit\n");
        exit(0);
    }
    else if(atoi(arg->cmd[i]))
    {
        printf("exit\n");
        exit(atoi(arg->cmd[i]));
    }
    else if (!atoi(arg->cmd[i]))
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n", arg->cmd[i]);
        exit(2);
    }
    // else
    // {
        
    // }
    return 0;
}
