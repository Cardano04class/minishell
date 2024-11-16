/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expanded.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:37:20 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:38:04 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_expanded(int i, char *expanded_line)
{
	char	*final_line;

	if (!expanded_line)
	{
		remove_empty_arg(i);
		return ;
	}
	final_line = remove_quotes(expanded_line);
	free(expanded_line);
	if (!final_line)
	{
		remove_empty_arg(i);
		return ;
	}
	g_mini.command->cmd[i] = final_line;
}
