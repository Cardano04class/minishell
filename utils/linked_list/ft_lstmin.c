/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:05:05 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/04 11:41:29 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstmin(t_list *stack_a)
{
	t_list	*min;

	min = stack_a;
	while (stack_a->next != NULL)
	{
		if (stack_a->next->content < min->content)
			min = stack_a->next;
		stack_a = stack_a->next;
	}
	return (min);
}
