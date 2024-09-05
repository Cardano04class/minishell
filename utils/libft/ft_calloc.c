/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:49:12 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 11:38:28 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > 0xffffffff / size)
	{
		return (NULL);
	}
	ptr = malloc(count * size);
	if (!ptr)
	{
		return (NULL);
	}
	else
	{
		ft_bzero(ptr, count * size);
	}
	return (ptr);
}
