/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:26:06 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/08 22:18:43 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*ft_heredoc_new(char *delimiter)
{
	t_heredoc	*new;

	new = _malloc(sizeof(t_cmd), 'm');
	new->delimiter = delimiter;
	new->next = NULL;
	return (new);
}
