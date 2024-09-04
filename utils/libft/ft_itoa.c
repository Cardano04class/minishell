/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:58:36 by mobouifr          #+#    #+#             */
/*   Updated: 2023/11/27 22:01:15 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nstrlen(int b)
{
	int	i;

	i = 0;
	if (b == 0)
	{
		return (1);
	}
	while (b != 0)
	{
		i++;
		b = b / 10;
	}
	return (i);
}

static void	ft_maker(char *p, int len, int j, long nb)
{
	while (len > 0)
	{
		if (len == 1 && j == 1)
			p[0] = '-';
		else
		{
			p[len - 1] = (nb % 10) + 48;
			nb = nb / 10;
		}
		len--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*p;
	int		i;
	int		j;
	long	nb;

	i = 0;
	j = 0;
	nb = (long)n;
	if (nb < 0)
	{
		nb = nb * (-1);
		len = ft_nstrlen(nb) + 1;
		j = 1;
	}
	else
	{
		len = ft_nstrlen(nb);
	}
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	ft_maker(p, len, j, nb);
	return (p);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
}*/
