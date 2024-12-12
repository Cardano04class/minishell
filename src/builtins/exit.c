/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:07:23 by mamir             #+#    #+#             */
/*   Updated: 2024/12/12 19:14:01 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_shell(t_cmd *arg)
{
	int					i;
	unsigned long long	num;
	int					is_numeric;
	int					j;

	i = 1;
	is_numeric = 1;
	
	if (arg->next->files->type != PIPE)
		
	printf("exit\n");
	if (!arg->cmd[i])
		exit(0);
	j = 0;
	while (arg->cmd[i][j])
	{
		if (!ft_isdigit(arg->cmd[i][j])
			&& !(j == 0 && (arg->cmd[i][j] == '-' || arg->cmd[i][j] == '+')))
		{
			is_numeric = 0;
			break ;
		}
		j++;
	}
	if (!is_numeric)
	{
		write(2, "minishell: exit: ", 17);
		write(2, arg->cmd[i], strlen(arg->cmd[i]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	num = ft_atoi(arg->cmd[i]);
	if (arg->cmd[i + 1])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit(num % 256);
}
