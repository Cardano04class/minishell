/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:58:21 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 13:05:03 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_char(t_var *var)
{
	var->expanded_len++;
	var->i++;
}

void	name_length(char *content, int *i, t_env *env, t_var *var)
{
	int		name_len;
	char	*var_name;
	char	*var_value;

	name_len = 0;
	while (content[*i] && (ft_isalnum(content[*i]) || content[*i] == '_'))
	{
		name_len++;
		(*i)++;
	}
	if (name_len > 0)
	{
		var_name = _malloc(name_len + 1, 'm');
		ft_strncpy(var_name, &content[*i - name_len], name_len);
		var_name[name_len] = '\0';
		var_value = expand_variable(env, var_name);
		if (var_value)
		{
			var->expanded_len += ft_strlen(var_value);
		}
	}
}

int	exit_status_len(char *content, t_var *var, int *i)
{
	if (content[*i] == '?')
	{
		var->exit_status = ft_itoa(g_mini.exit_status);
		if (var->exit_status)
			var->expanded_len += ft_strlen(var->exit_status);
		(*i)++;
		return (1);
	}
	return (0);
}

int	lone_dollar_case(char *content, t_var *var, int *i)
{
	if (content[*i] == '\0')
	{
		var->expanded_len++;
		return (1);
	}
	return (0);
}
