/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:09:54 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/06 21:04:31 by mamir            ###   ########.fr       */
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
}
