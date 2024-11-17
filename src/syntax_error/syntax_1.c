/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:19:36 by mamir             #+#    #+#             */
/*   Updated: 2024/11/17 15:20:11 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	create_error(t_error_type type, char *token)
{
	t_error	error;

	error.type = type;
	error.token = token;
	return (error);
}

void	print_error(t_error error)
{
	if (error.type == UNCLOSED_QUOTES)
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
	else if (error.type == INVALID_POSITION || error.type == PIPE_AT_START
		|| error.type == MISSING_CONTEXT)
	{
		ft_putstr_fd("syntax error: '", 2);
		ft_putstr_fd(error.token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error.type == CONSECUTIVE_SPECIAL)
		ft_putstr_fd("syntax error: consecutive special symbols\n", 2);
}
