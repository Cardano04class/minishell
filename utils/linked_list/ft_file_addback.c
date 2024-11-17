/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:46:31 by mobouifr          #+#    #+#             */
/*   Updated: 2024/11/17 15:36:25 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file_addback(t_file *new)
{
	t_file	*tmp;

	/**  if (!g_mini.command)
	 	return ;**/
	if (!g_mini.command->files)
	{
		g_mini.command->files = new;
		return ;
	}
	tmp = g_mini.command->files;
	printf("testttt %p\n", tmp);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
