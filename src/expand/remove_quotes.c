/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:43:28 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 13:00:18 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->in_single_quote = 0;
	var->in_double_quote = 0;
	var->expanded_len = 0;
	var->status_len = 0;
}

void	name_expansion(t_var *var, t_env *env, char *content, char *expanded)
{
	int		name_len;
	char	*var_name;
	char	*var_value;
	int		value_len;

	name_len = 0;
	while (content[var->i] && (ft_isalnum(content[var->i])
			|| content[var->i] == '_'))
	{
		name_len++;
		var->i++;
	}
	if (name_len > 0)
	{
		var_name = _malloc(name_len + 1, 'm');
		ft_strncpy(var_name, &content[var->i - name_len], name_len);
		var_name[name_len] = '\0';
		var_value = expand_variable(env, var_name);
		if (var_value)
		{
			value_len = ft_strlen(var_value);
			ft_strcpy(&expanded[var->j], var_value);
			var->j += value_len;
		}
	}
}

void	handle_dollar_expansion(char *content, char *expanded, t_var *var,
		t_env *env)
{
	var->i++;
	if (content[var->i] == '\0' || content[var->i] == '"'
		|| content[var->i] == '\'')
	{
		expanded[var->j++] = '$';
		return ;
	}
	if (content[var->i] == '?')
	{
		var->exit_status = ft_itoa(g_mini.exit_status);
		if (var->exit_status)
		{
			var->status_len = ft_strlen(var->exit_status);
			ft_strcpy(&expanded[var->j], var->exit_status);
			var->j += var->status_len;
		}
		var->i++;
		return ;
	}
	name_expansion(var, env, content, expanded);
}

char	*remove_quotes_and_expand(t_env *env, char *content)
{
	int		expanded_len;
	char	*expanded_content;
	t_var	*var;

	expanded_len = calculate_expand_length(content, env);
	expanded_content = _malloc(expanded_len + 1, 'm');
	var = _malloc(sizeof(t_var), 'm');
	init_var(var);
	while (content[var->i])
	{
		if (handle_quotes(var, content))
			continue ;
		if (content[var->i] == '$' && !var->in_single_quote)
		{
			handle_dollar_expansion(content, expanded_content, var, env);
		}
		else
			expanded_content[var->j++] = content[var->i++];
	}
	expanded_content[var->j] = '\0';
	return (expanded_content);
}
