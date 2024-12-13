/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:36:27 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/13 02:17:10 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_exit_builtin(t_cmd *commmand) 
{
    ft_exit(commmand);
}

void handle_echo(t_cmd *commmand) 
{
    if (ft_strcmp(commmand->cmd[1], "$?") == 0) 
        printf("%d\n", g_mini.exit_status);
}

int capture_exit_status(int status) 
{
    if (WIFEXITED(status)) 
    {
        return (WEXITSTATUS(status));
    } 
    else if (WIFSIGNALED(status)) 
    {
        return (128 + WTERMSIG(status));
    }
    return (1);
}
