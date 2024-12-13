/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:36:27 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/13 17:45:13 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_exit_builtin(t_cmd *commmand) 
// {
//     ft_exit(commmand);
// }

void handle_echo(t_cmd *commmand) 
{
    if (ft_strcmp(commmand->cmd[1], "$?") == 0) 
        printf("%d\n", g_mini.exit_status);
}

int capture_exit_status(int status) 
{
    if (WIFEXITED(status)) 
    {
        puts(":1");
        return (WEXITSTATUS(status));
    } 
    else if (WIFSIGNALED(status)) 
    {
        puts("2");
        return (128 + WTERMSIG(status));
    }
        puts("3");
    return (1);
}
