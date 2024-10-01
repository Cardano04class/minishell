/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:37:25 by mobouifr          #+#    #+#             */
/*   Updated: 2024/10/01 17:49:51 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_addback(t_cmd **command, t_cmd *new)
{
	t_cmd	*tmp;

	if (!command)
		return ;
	if (!*command)
	{
		(*command) = new;
		return ;
	}
	tmp = *command;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

