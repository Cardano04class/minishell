/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 22:55:10 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arguments(char **args, int i, int last_arg, bool n_option)
{
	while (args[i])
	{
		print_argument(args[i]);
		print_separator(n_option, i, last_arg);
		i++;
	}
}

int	echo(char **args)
{
	int		i;
	bool	n_option;
	int		last_arg;

	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	n_option = false;
	i = 1;
	last_arg = count_arguments(args);
	i = handle_n_option(args, i, &n_option);
	print_arguments(args, i, last_arg, n_option);
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
