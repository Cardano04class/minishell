/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:28:01 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/09 16:37:44 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = malloc(ft_strlen(s1) + 1);
	if (!s2)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char	s1[] = "cola aloc";

	// printf("ft_strdup : %s", ft_strdup(s1));
	printf("strdup : %s", strdup(s1));
	return (0);
}
*/
