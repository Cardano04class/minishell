/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:38:01 by mamir             #+#    #+#             */
/*   Updated: 2024/12/20 17:00:32 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_numeric_arg(const char *arg)
{
	size_t	num_count;
	int		sign;

	sign = 1;
	if (!validate_chars(arg, &num_count) || num_count == 0 || num_count > 19)
		return (0);
	if (num_count == 19 && check_overflow(arg, sign))
		return (0);
	return (1);
}

int	is_last_command(t_cmd *current)
{
	t_cmd	*temp;

	temp = current;
	while (temp)
	{
		if (temp->next == NULL)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	handle_exit_error(char *arg)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	_malloc(0, 'f');
	exit(2);
}

void	handle_too_many_arguments(void)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	g_mini.exit_status = 1;
}

void	exit_with_status(int status)
{
	ft_putstr_fd("exit\n", 2);
	_malloc(0, 'f');
	exit(status);
}
