/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:06:42 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 14:12:48 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_and_process_arg(t_cmd *current, char *arg)
{
	if (!is_valid_numeric_arg(arg))
	{
		if (is_last_command(current))
			handle_exit_error(arg);
		return (0);
	}
	g_mini.exit_status = (unsigned char)ft_atol(arg);
	return (1);
}

static void	process_exit_command(t_cmd *current)
{
	char	*arg;

	arg = current->cmd[1];
	if (arg && !validate_and_process_arg(current, arg))
		return ;
	if (current->cmd[2])
	{
		if (is_last_command(current))
			handle_too_many_arguments();
		return ;
	}
	if (is_last_command(current) && g_mini.exit_pipe != 1)
		exit_with_status(g_mini.exit_status);
}

void	ft_exit(t_cmd *data)
{
	t_cmd	*current;

	current = data;
	while (current)
	{
		if (ft_strcmp(current->cmd[0], "exit") == 0)
		{
			if (!current->cmd[1])
			{
				if (is_last_command(current) && g_mini.exit_pipe != 1)
					exit_with_status(g_mini.exit_status);
			}
			else
				process_exit_command(current);
			return ;
		}
		current = current->next;
	}
}
