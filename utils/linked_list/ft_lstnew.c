/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:50:10 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/04 09:44:37 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lstnew(char *content, t_token type)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}
