/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:56:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 13:16:52 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_case(t_var *var, char *content, t_env *env)
{
	var->i++;
	if (lone_dollar_case(content, var, &var->i))
		return ;
	if (var->in_double_quote)
		var->expanded_len++;
	if (exit_status_len(content, var, &var->i))
		return ;
	name_length(content, &var->i, env, var);
}

int	single_quotes_skip(char *content, int *i, t_var *var)
{
	if (content[*i] == '\'' && !var->in_double_quote)
	{
		var->in_single_quote = !var->in_single_quote;
		if (var->in_single_quote)
			(*i)++;
		return (1);
	}
	return (0);
}

int	double_quotes_skip(char *content, int *i, t_var *var)
{
	if (content[*i] == '"' && !var->in_single_quote)
	{
		var->in_double_quote = !var->in_double_quote;
		if (var->in_double_quote)
			(*i)++;
		return (1);
	}
	return (0);
}

int	handle_quotes(t_var *var, char *content)
{
	if (single_quotes_skip(content, &var->i, var))
		return (1);
	if (double_quotes_skip(content, &var->i, var))
		return (1);
	return (0);
}

int	calculate_expand_length(char *content, t_env *env)
{
	t_var	*var;

	var = _malloc(sizeof(t_var), 'm');
	init_var(var);
	while (content[var->i])
	{
		if (handle_quotes(var, content))
			continue ;
		if (content[var->i] == '$' && !var->in_single_quote)
			handle_dollar_case(var, content, env);
		else
			process_char(var);
	}
	return (var->expanded_len);
}
