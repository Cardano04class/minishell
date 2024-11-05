/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:12:03 by mamir             #+#    #+#             */
/*   Updated: 2024/11/05 23:00:01 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **str)
{
	int		flag;
	int		lock;
	int		i;
	bool	is_first_argument;
	int		j;
	bool	all_n;

	// printf("str[1] : %s\n", str[1]);
	flag = false;
	lock = false;
	i = 1;
	is_first_argument = true;
	if (str[1] == NULL)
		printf("\n");
	while (str[i])
	{
		if (is_first_argument && str[i][0] == '-' && str[i][1] != '\0')
		{
			j = 1;
			all_n = true;
			while (str[i][j])
			{
				if (str[i][j] != 'n')
				{
					all_n = false;
					break ;
				}
				j++;
			}
			if (all_n)
			{
				lock = true;
				i++;
				continue ;
			}
		}
		is_first_argument = false;
		j = 0;
		while (str[i][j])
		{
			write(1, &str[i][j], 1);
			j++;
		}
		if (str[i + 1])
			write(1, " ", 1);
		flag = true;
		i++;
	}
	if (!lock && flag)
		write(1, "\n", 1);
	return (0);
}
