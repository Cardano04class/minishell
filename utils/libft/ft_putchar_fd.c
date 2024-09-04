/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:04:37 by mobouifr          #+#    #+#             */
/*   Updated: 2023/11/22 15:52:57 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd != -1)
	{
		write(fd, &c, 1);
	}
}
// int	main(void)
// {
//  	int	fd;

// 	fd = open("Z.txt", O_WRONLY | O_CREAT);
//  	ft_putchar_fd('5', fd);
// 	close(fd);
//  	return (0);
//  }
