/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_addback.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:30 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/20 09:10:19 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_addback(t_heredoc **heredoc, t_heredoc *new)
{
	t_heredoc	*tmp;

	if (!heredoc)
		return ;
	if (!*heredoc)
	{
		(*heredoc) = new;
		return ;
	}
	tmp = *heredoc;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
