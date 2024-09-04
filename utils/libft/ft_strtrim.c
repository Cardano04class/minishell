/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:52:31 by mobouifr          #+#    #+#             */
/*   Updated: 2023/12/09 17:58:59 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*s2;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (len > i && s1[len - 1] && ft_strchr(set, s1[len - 1]))
		len--;
	if (len == i)
		return (ft_strdup(""));
	s2 = (char *)malloc((len - i + 1));
	if (s2 == NULL)
		return (NULL);
	j = 0;
	while (i < len)
		s2[j++] = s1[i++];
	s2[j] = '\0';
	return (s2);
}
/*
#include <stdio.h>

int	main(void)
{
	char const	s1[] = "gvigeeeeeeeeeeegigive";

	printf("%s", ft_strtrim(s1, "give"));
	return (0);
}*/