/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:02:24 by mamir             #+#    #+#             */
/*   Updated: 2024/12/08 22:12:07 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garbage	*new_garbage(void *content)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
    new->ptr = content;
	new->next = NULL;
	return (new);
}

void	addback_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	clear_garbage(t_garbage **lst)
{
	t_garbage	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->ptr);
		free(*lst);
		*lst = tmp;
	}
}

void    *_malloc(size_t size, char op)
{
    void    *ptr;
    static  t_garbage *trash;

    if (op == 'f')
    {
        clear_garbage(&trash);
        trash = NULL;
        return ;
    }
    ptr = malloc(size);
    if (!ptr)
    {
        clear_garbage(&trash);
        exit (1);
    }
    addback_garbage(&trash, new_garbage(ptr));
    return (ptr);
}
