/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdisplay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:18:39 by mobouifr          #+#    #+#             */
/*   Updated: 2024/10/01 10:32:00 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdisplay(t_list *stack)
{
	printf("lst size : %d\n\n", ft_lstsize(stack));
	while (stack != NULL)
	{
		printf("content : %s\n",stack->content);
		if (stack->prev != NULL)
			printf("prev content : %s\n",stack->prev->content);
		if (stack->type == 0)
			printf("type : WORD\n");
		if (stack->type == 1)
			printf("type : INRED\n");
		if (stack->type == 2)
			printf("type : OUTRED\n");
		if (stack->type == 3)
			printf("type : APPEND\n");
		if (stack->type == 4)
			printf("type : HERDOC\n");
		if (stack->type == 5)
			printf("type : PIPE\n");
		stack = stack->next;
		puts("");
	}
}

