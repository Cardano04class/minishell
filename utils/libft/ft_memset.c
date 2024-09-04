/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:37:22 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/10 15:13:38 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	int ptr[] = {2, 3, 4};
	printf("%d\n", ptr[1]);
	
	ft_memset((char *)ptr + 4, 57, 1);
	ft_memset((char *)ptr + 5, 5, 1);
	ft_memset((char *)ptr + 6, 0, 1);
	ft_memset((char *)ptr + 7, 0, 1);
	printf("%d", ptr[1]);
	return (0);
}
*/
