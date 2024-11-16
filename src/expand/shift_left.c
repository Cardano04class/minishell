/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:41:10 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:41:18 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_left(int i)
{
	while (g_mini.command->cmd[i + 1])
	{
		g_mini.command->cmd[i] = g_mini.command->cmd[i + 1];
		i++;
	}
	g_mini.command->cmd[i] = NULL;
}
