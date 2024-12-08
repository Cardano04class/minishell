/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:43:34 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/08 22:18:39 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*ft_file_new(char *filename, t_token type, char *delimiter)
{
	t_file	*new;

	new = _malloc(sizeof(t_file), 'm');
	new->filename = filename;
	new->delimiter = delimiter;
	new->type = type;
	new->next = NULL;
	return (new);
}
