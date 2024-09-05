/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 06:39:10 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 11:40:41 by mamir            ###   ########.fr       */
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
