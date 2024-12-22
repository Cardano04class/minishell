/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:49:16 by mamir             #+#    #+#             */
/*   Updated: 2024/12/22 21:56:53 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_mini;

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
	{
		prompt(env);
		return (g_mini.exit_status);
	}
	else
		return (1);
}
