/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_addback.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:30 by mobouifr          #+#    #+#             */
/*   Updated: 2024/11/26 17:33:56 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_addback(t_heredoc *new)
{
	t_heredoc	*tmp;

	if (g_mini.command->heredoc == NULL)
	{
		g_mini.command->heredoc = new;
		return ;
	}
	tmp = g_mini.command->heredoc;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
