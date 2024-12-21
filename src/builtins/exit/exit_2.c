/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:35:13 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 15:37:47 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_overflow(const char *num_start, const char *limit)
{
	while (*num_start && ft_isdigit(*num_start))
	{
		if (*num_start > *limit)
			return (1);
		else if (*num_start < *limit)
			break ;
		num_start++;
		limit++;
	}
	return (0);
}

const char	*skip_leading(const char *arg, int *sign)
{
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			*sign = -1;
		arg++;
	}
	while (*arg == '0')
		arg++;
	return (arg);
}

int	check_overflow(const char *arg, int sign)
{
	const char	*max = "9223372036854775807";
	const char	*min = "9223372036854775808";
	const char	*num_start;

	num_start = skip_leading(arg, &sign);
	if (sign == 1)
		return (is_overflow(num_start, max));
	return (is_overflow(num_start, min));
}

int	validate_chars(const char *arg, size_t *num_count)
{
	size_t	i;

	i = 0;
	*num_count = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] == '0')
		i++;
	while (ft_isdigit(arg[i]))
	{
		(*num_count)++;
		i++;
	}
	while (ft_isspace(arg[i]))
		i++;
	return (arg[i] == '\0');
}
