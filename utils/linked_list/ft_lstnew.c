/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:50:10 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/13 02:14:04 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_2(char *content, t_token token_type, int separated_by_space)
{
	t_list	*new;

	new = _malloc(sizeof(t_list), 'm');
	if (!new)
		return (NULL);
	new->content = content;
	new->type = token_type;
	new->separated_by_space = separated_by_space;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_list	*ft_lstnew(char *content, t_token token_type)
{
	t_list	*new;

	new = _malloc(sizeof(t_list), 'm');
	if (!new)
		return (NULL);
	new->content = content;
	new->type = token_type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
