/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:56 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/10 15:31:28 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	//const char		s1[] = "02";
	//const char		s2[] = "00";
	unsigned char	ft_strncm;
	//unsigned char	strncm;

	ft_strncm = ft_strncmp("02", "00", 2);
	//strncm = strncmp(s1, s2, 2);
	//printf("ft_strncmp : %d", ft_strncmp("02", "00", 2));
	printf("strncmp : %d\n", ft_strncm);
	return (0);
}*/