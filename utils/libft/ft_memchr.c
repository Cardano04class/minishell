/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:34:32 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/11 09:25:55 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*st;

	st = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (st[i] == (unsigned char)c)
		{
			return (&st[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*s;

	s = NULL;
	//printf("ft_memchr : %s\n", ft_memchr(s, 7, 10));
	printf("memchr : %s", memchr(s, 7, 10));
}
*/