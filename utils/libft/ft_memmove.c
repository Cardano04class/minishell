/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:59:04 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/10 14:39:14 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = -1;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			d[i] = s[i];
	}
	return (d);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	unsigned char		ptr[] = "qwertyuiop";
	unsigned char		*dst;
	unsigned const char	*src;

	dst = ptr + 5;
	src = ptr;
	printf("ft_memmove: %s\n", ft_memmove(dst, NULL, 4));
	//printf("memmove: %s\n", memmove(dst, NULL, 3));
	return (0);
}
*/