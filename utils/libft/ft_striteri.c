/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:13:06 by mobouifr          #+#    #+#             */
/*   Updated: 2023/11/27 20:58:30 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (!s || !f)
	{
		return ;
	}
	while (s && f && s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	ft_touppe(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
	{
		*c = *c - 32;
	}
}
int	main(void)
{
	char	*s = "dgtrg";
	ft_striteri(s , ft_touppe);
	printf("%s", s);
	return (0);
}*/