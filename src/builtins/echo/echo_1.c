/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:54:54 by mamir             #+#    #+#             */
/*   Updated: 2024/12/17 22:42:18 by mamir            ###   ########.fr       */
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

void	print_separator(bool n_option, int i, int last_arg)
{
	if (i < last_arg - 1 && !n_option)
		write(1, " ", 1);
}

int	count_arguments(char **args)
{
	int	last_arg;

	last_arg = 0;
	while (args[last_arg])
	{
		last_arg++;
	}
	return (last_arg);
}

int	handle_n_option(char **args, int i, bool *n_option)
{
	while (args[i] && is_n_option(args[i]))
	{
		*n_option = true;
		i++;
	}
	return (i);
}

