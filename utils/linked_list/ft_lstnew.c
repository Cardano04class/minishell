/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:50:10 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/08 22:00:40 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *content, t_token type)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = content;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	
	new->next = NULL;
	return (new);
}
