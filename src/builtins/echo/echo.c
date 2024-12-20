/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/12/20 18:21:08 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_case(char *args, int *i, bool *n_option, int last)
{
	if (is_n_option(args) && *i < last)
	{
		*n_option = true;
		(*i)++;
		return (1);
	}
	*n_option = false;
	return (0);
}

int	get_last_arg(char **args)
{
	int	last_arg;

	last_arg = 0;
	while (args[last_arg])
		last_arg++;
	return (last_arg);
}

int	echo(char **args)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	while (args[i] && is_n_option(args[i]))
	{
		n_option = true;
		i++;
	}
	while (args[i])
	{
		print_argument(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
