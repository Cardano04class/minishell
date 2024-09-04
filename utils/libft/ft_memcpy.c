/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:09:38 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/11 10:51:17 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*f;
	const unsigned char	*s;

	if (src == NULL && dst == NULL)
		return (NULL);
	if (src == dst)
		return (dst);
	f = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		f[i] = s[i];
		i++;
	}
	return (f);
}
/*
#include "libft.h"
#include <stdio.h>

int main(void)
{
    int src[] = {1, 1, 1, 1, 1};
    int dst[] = {0, 0, 0, 0, 0};
	size_t i = 0;

    ft_memcpy(dst + 2, src, 8);
	while (i < 5)
	{
        printf("%d ", dst[i]);
		i++;
	}
    return 0;
}
*/