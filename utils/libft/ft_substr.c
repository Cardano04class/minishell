/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:09:54 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/10 15:39:43 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*str;

	if (s == NULL)
		return (NULL);
	l = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start] != '\0' && l < len)
	{
		str[l] = s[start];
		start++;
		l++;
	}
	str[l] = '\0';
	return (str);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char const	s[] = "qwertyuiop";

	printf("%s", ft_substr(s, 8, 5));
	return (0);
}*/