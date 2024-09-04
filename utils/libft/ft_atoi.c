/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:50:31 by mobouifr          #+#    #+#             */
/*   Updated: 2024/08/29 17:57:00 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include "libft.h"
#include <limits.h>

void	minmaxcheck(long v, char **string, int *all_nums)
{
	if (v > INT_MAX || v < INT_MIN)
	{
		write(2, "Error\n", 6);
		ft_free(string);
		free(all_nums);
		exit(1);
	}
}

void	digitcheck(char *str, int i, char **string, int *all_nums)
{
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i++]))
		{
			write(2, "Error\n", 6);
			ft_free(string);
			free(all_nums);
			exit(1);
		}
	}
}

int	ft_atoi(char *str, char **string, int *all_nums)
{
	int		i;
	long	v;
	int		s;

	i = 0;
	v = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i + 1] != '\0' && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		v = v * 10 + (str[i] - 48);
		minmaxcheck((v * s), string, all_nums);
		i++;
	}
	digitcheck(str, i, string, all_nums);
	v *= s;
	return (v);
}
