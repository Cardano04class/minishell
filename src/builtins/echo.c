/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/12/14 22:58:42 by mamir            ###   ########.fr       */
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

int	print_argument(char *arg)
{
	int	j;

	j = 0;
	if (arg[0] == '\0')
		return (0);
	while (arg[j])
	{
		write(1, &arg[j], 1);
		j++;
	}
	return (1);
}

void	print_arguments_one_at_a_time(char **args, int i)
{
	if (args[i])
	{
		print_argument(args[i]);
	}
}

int	echo(char **args)
{
	int		i;
	bool	n_option;
	int		last_arg;

	i = 1;
	n_option = false;
	last_arg = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[last_arg])
		last_arg++;
	while (args[i])
	{
		if (is_n_option(args[i]))
		{
			n_option = true;
			i++;
			continue ;
		}
		print_argument(args[i]);
		if (i < last_arg - 1 && !n_option)
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
