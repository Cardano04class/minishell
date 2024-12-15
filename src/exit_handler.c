/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:36:27 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/15 14:56:52 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
