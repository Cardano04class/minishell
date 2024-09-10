/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:16:37 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/10 14:18:32 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static int	wrdcount(char const *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
		{
			count++;
			while (str[i] != '\0' && !ft_isspace(str[i]))
				i++;
		}
		else if (ft_isspace(str[i]))
			i++;
	}
	return (count);
}

static size_t	wrdlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && !ft_isspace(s[i]))
	{
		i++;
	}
	return (i);
}

static char	**ft_free(char **ptr, size_t j)
{
	while (j > 0)
	{
		free(ptr[j - 1]);
		j--;
	}
	free(ptr);
	return (NULL);
}

static char	*help(char const *s)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(wrdlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (s[i] != '\0' && !ft_isspace(s[i]))
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_ssplit(char const *s)
{
	char	**ptr;
	size_t	i;

	if (!s)
		return (NULL);
	ptr = (char **)malloc((wrdcount(s) + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (ft_isspace(*s))
			s++;
		if (*s != '\0')
		{
			ptr[i] = help(s);
			if (ptr[i] == NULL)
				return (ft_free(ptr, i));
			i++;
		}
		while (*s != '\0' && ft_isspace(*s))
			s++;
	}
	ptr[i] = NULL;
	return (ptr);
}
