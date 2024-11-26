/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:37:00 by mamir             #+#    #+#             */
/*   Updated: 2024/11/17 15:37:28 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_clear(t_env **lst)
{
	t_env	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}
