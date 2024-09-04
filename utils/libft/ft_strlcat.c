/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:39:10 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/10 15:22:31 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
	{
		return (src_len);
	}
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
	{
		return (src_len + dstsize);
	}
	i = 0;
	j = dst_len;
	while (src[i] != '\0' && (j + i) < (dstsize - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (dst_len + src_len);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char		dst[] = "He36";
	const char	src[] = "world!";

	printf("%zu\n", ft_strlcat(dst, dst, sizeof(dst)));
	//printf("%zu\n", strlcat(dst, dst, 5));
	printf("%s", dst);
	return (0);
}*/