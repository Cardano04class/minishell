/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:50:39 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/08 22:32:25 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wrdcount(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else if (str[i] == c)
			i++;
	}
	return (count);
}

static size_t	wrdlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

static char	*help(char const *s, char c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)_malloc(wrdlen(s, c) + 1, 'm');
	if (!ptr)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;

	if (!s)
		return (NULL);
	ptr = (char **)_malloc((wrdcount(s, c) + 1) * sizeof(char *), 'm');
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			ptr[i] = help(s, c);
			i++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	ptr[i] = NULL;
	return (ptr);
}
