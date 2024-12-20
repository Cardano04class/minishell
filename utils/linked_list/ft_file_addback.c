/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:46:31 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/20 09:10:13 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file_addback(t_file *new, t_cmd *command)
{
	t_file	*tmp;

	if (command->files == NULL)
	{
		command->files = new;
		return ;
	}
	tmp = command->files;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
