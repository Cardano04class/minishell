/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:36:27 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/04 17:21:20 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_exit_builtin(t_cmd *commmand) 
{
    if (commmand->cmd[1])
        exit(ft_atoi(commmand->cmd[1]));
    else
        exit(g_mini.exit_status);
}

void handle_echo(t_cmd *commmand) 
{
    if (strcmp(commmand->cmd[1], "$?") == 0) 
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