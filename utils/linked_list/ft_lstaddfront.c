/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:52:14 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/04 11:41:03 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstaddfront(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	(*lst) = new;
	(*lst)->next = tmp;
}
