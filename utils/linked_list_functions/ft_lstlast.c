/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:35:29 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/04 08:46:14 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (1);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
