/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:10:50 by codespace         #+#    #+#             */
/*   Updated: 2024/11/05 22:22:13 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to shift commands in the command array after removing an entry
void shift_commands(char **cmd, int index)
{
    int j = index;

    free(cmd[index]);
    while (cmd[j + 1])
    {
        cmd[j] = cmd[j + 1];
        j++;
    }
    cmd[j] = NULL;
}

