/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:26:15 by mobouifr          #+#    #+#             */
/*   Updated: 2023/11/28 14:12:23 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	n_zero_min(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	arr[10];

	if (fd != -1)
	{
		i = 0;
		n_zero_min(n, fd);
		if (n < 0 && n != -2147483648)
		{
			write(fd, "-", 1);
			n = -n;
		}
		while (n > 0)
		{
			arr[i] = (n % 10) + 48;
			n = n / 10;
			i++;
		}
		while (i > 0)
		{
			i--;
			write(fd, &arr[i], 1);
		}
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(-10000043, 1);
}*/