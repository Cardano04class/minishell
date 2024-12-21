/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:11:44 by mamir             #+#    #+#             */
/*   Updated: 2024/12/21 10:26:37 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minmaxcheck(long v)
{
	if (v > LONG_MAX || v < LONG_MIN)
		exit(1);
}

static void	digitcheck(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i++]))
			exit(1);
	}
}

long	ft_atol(char *str)
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
		minmaxcheck((v * s));
		i++;
	}
	digitcheck(str, i);
	v *= s;
	return (v);
}
