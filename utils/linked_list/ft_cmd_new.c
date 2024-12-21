/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:08 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/16 12:07:32 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(char **content)
{
	t_cmd	*new;

	new = _malloc(sizeof(t_cmd), 'm');
	new->cmd = content;
	new->files = NULL;
	new->next = NULL;
	return (new);
}
