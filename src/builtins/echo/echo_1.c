/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:54:54 by mamir             #+#    #+#             */
/*   Updated: 2024/12/21 09:29:35 by mamir            ###   ########.fr       */
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
	return (str[j] == '\0');
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
