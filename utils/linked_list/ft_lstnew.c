/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:50:10 by mobouifr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/04 10:26:48 by mamir            ###   ########.fr       */
=======
/*   Updated: 2024/09/04 11:41:32 by mobouifr         ###   ########.fr       */
>>>>>>> main
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
	return (new);
}
