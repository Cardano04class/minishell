/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:26:06 by mobouifr          #+#    #+#             */
/*   Updated: 2024/10/02 15:38:02 by mobouifr         ###   ########.fr       */
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