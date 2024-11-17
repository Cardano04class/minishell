/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:33:46 by mamir             #+#    #+#             */
/*   Updated: 2024/11/17 15:33:48 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envsize(t_env *env)
{
	int	count;

	count = 0;
	if (env == NULL)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		count++;
	}
	return (count);
}
