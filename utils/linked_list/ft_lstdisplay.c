/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdisplay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:18:39 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 10:25:35 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdisplay(t_list *stack)
{
	printf("lst size : %d\n", ft_lstsize(stack));
	while (stack != NULL)
	{
		printf("node->content : %s\n",stack->content);
		if (stack->type == 0)
			printf("node->type : WORD\n");
		if (stack->type == 1)
			printf("node->type : INRED\n");
		if (stack->type == 2)
			printf("node->type : OUTRED\n");
		if (stack->type == 3)
			printf("node->type : APPEND\n");
		if (stack->type == 4)
			printf("node->type : HERDOC\n");
		if (stack->type == 5)
			printf("node->type : PIPE\n");
		stack = stack->next;
	}
}

