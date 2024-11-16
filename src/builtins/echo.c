/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 14:40:52 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_n_option(char *str)
{
	int	j;

	if (str[0] != '-' || str[1] != 'n')
		return (false);
	j = 2;
	while (str[j] == 'n')
		j++;
	if (str[j] == '\0')
		return (true);
	return (false);
}

int	print_arguments(char **str, int i)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (i);
}

int	echo(char **str)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	if (str[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (str[i] && is_n_option(str[i]))
	{
		n_option = true;
		i++;
	}
	print_arguments(str, i);
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
