/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:26:06 by mobouifr          #+#    #+#             */
/*   Updated: 2024/11/17 15:34:57 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*ft_heredoc_new(char *delimiter)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_cmd));
	new->delimiter = delimiter;
	new->content = NULL;
	new->next = NULL;
	return (new);
}
