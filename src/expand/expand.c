/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:36:55 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:37:02 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_env *env)
{
	int		i;
	char	*expanded_line;

	i = 0;
	while (g_mini.command->cmd[i])
	{
		expanded_line = expand_variables(env, g_mini.command->cmd[i]);
		process_expanded(i, expanded_line);
		i++;
	}
}
