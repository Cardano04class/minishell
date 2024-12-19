/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:54:54 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 13:12:27 by mamir            ###   ########.fr       */
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
	g_mini.exit_status = 0;
	return (1);
}

void	print_arguments_one_at_a_time(char **args, int i)
{
	if (args[i])
	{
		print_argument(args[i]);
	}
}
