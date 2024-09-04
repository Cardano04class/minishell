/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:49:12 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/10 15:39:46 by mobouifr         ###   ########.fr       */
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
/*
int	main(void)
{
	int	*ptr;

	ptr = ft_calloc(1, 0);
	printf("%p", ptr);
	*ptr = 1;
	printf("\n%i", *ptr);
	return (0);
}*/