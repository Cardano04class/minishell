/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:43:28 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 00:50:46 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_var(t_var *var)
{
    var->i = 0;
	var->in_single_quote = 0;
	var->in_double_quote = 0;
	var->expanded_len = 0;
}

void name_length(char *content, int *i, t_env *env, t_var *var)
{
    int name_len;
    char *var_name;
    char *var_value;
    
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

int exit_status_len(char *content, t_var *var, int *i)
{
    char *exit_status;
    if (content[*i] == '?')
    {
        exit_status = ft_itoa(g_mini.exit_status);
        if (exit_status)
            var->expanded_len += ft_strlen(exit_status);
        (*i)++;
        return 1;
    }
    return 0;
}

int lone_dollar_case(char *content, t_var *var, int *i)
{
    if (content[*i] == '\0')
    {
		var->expanded_len++;
        return 1;
    }
    return 0;
}

void handle_dollar_case(t_var *var, char *content, t_env *env)
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
		return 1;
	}
	return 0;
}

int double_quotes_skip(char *content, int *i, t_var *var)
{
    if (content[*i] == '"' && !var->in_single_quote)
    {
        var->in_double_quote = !var->in_double_quote;
        if (var->in_double_quote)
            (*i)++;
        return 1;
    }
    return 0;
}

int handle_quotes(t_var *var, char *content)
{
    if(single_quotes_skip(content, &var->i, var))
            return 1;
    if (double_quotes_skip(content, &var->i, var))
            return 1;
    return 0;    
}

int calculate_expand_length(char *content, t_env *env)
{
    t_var *var;
    
    var = _malloc(sizeof(t_var), 'm');
    init_var(var);
    while (content[var->i])
    { 
		if (handle_quotes(var, content))
            continue ;
        if (content[var->i] == '$' && !var->in_single_quote)
            handle_dollar_case(var, content, env);
        else
        {
            var->expanded_len++;
            var->i++;
        }
    }
    return var->expanded_len;
}

char *remove_quotes_and_expand(t_env *env, char *content)
{
    int expanded_len = calculate_expand_length(content, env);
	char *expanded_content = _malloc(expanded_len + 1, 'm');
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
	char *var_value;
    char 	*var_name;
	int		value_len;
    int name_len;
    char *exit_status;
    int status_len = 0;
    while (content[i])
    {
        if (content[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            if (in_single_quote)
                i++;
            continue ;
        }
        if (content[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            if (in_double_quote)
                i++;
            continue ;
        }
        if (content[i] == '$' && !in_single_quote)
        {
            i++;
            if (content[i] == '\0' || content[i] == '"' || content[i] == '\'')
            {
                expanded_content[j++] = '$';
                continue ;
            }
            if (content[i] == '?')
            {
                exit_status = ft_itoa(g_mini.exit_status);
                if (exit_status)
                {
                    status_len = ft_strlen(exit_status);
                    ft_strcpy(&expanded_content[j], exit_status);
                    j += status_len;
                }
                i++;
                continue ;
            }
            name_len = 0;
            while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
            {
                name_len++;
                i++;
            }
            if (name_len > 0)
            {
                var_name = _malloc(name_len + 1, 'm');
                ft_strncpy(var_name, &content[i - name_len], name_len);
                var_name[name_len] = '\0';
                var_value = expand_variable(env, var_name);
                if (var_value)
                {
                    value_len = ft_strlen(var_value);
                    ft_strcpy(&expanded_content[j], var_value);
                    j += value_len;
                }
            }
        }
        else
            expanded_content[j++] = content[i++];
    }
    expanded_content[j] = '\0';
    return (expanded_content);
}
