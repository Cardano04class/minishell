/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_var_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:46 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:06:58 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var_value(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

int	get_var_name_length(char *content, int *i)
{
	int	name_len;

	name_len = 0;
	while (content[*i] && (ft_isalnum(content[*i]) || content[*i] == '_'))
	{
		name_len++;
		*i = *i + 1;
	}
	return (name_len);
}

int	get_var_value_length(char *content, int name_len, int i)
{
	char	*var_name;
	char	*var_value;
	int		expanded_len;

	expanded_len = 0;
	var_name = _malloc(name_len + 1, 'm');
	ft_strncpy(var_name, &content[i - name_len], name_len);
	var_name[name_len] = '\0';
	var_value = find_var_value(g_mini.env, var_name);
	if (var_value != NULL)
		expanded_len += ft_strlen(var_value);
	return (expanded_len);
}

int	calculate_var_expansion_length(char *content)
{
	int	i;
	int	expanded_len;
	int	name_len;

	i = 0;
	expanded_len = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$')
		{
			i++;
			if (char_is_null(content[i], &expanded_len)
				|| char_is_exit_holder(content[i], &expanded_len, &i))
				continue ;
			name_len = get_var_name_length(content, &i);
			if (name_len > 0)
				expanded_len += get_var_value_length(content, name_len, i);
		}
		else
		{
			expanded_len++;
			i++;
		}
	}
	return (expanded_len);
}

char	*get_var_value(char *content, int name_len, int i)
{
	char	*var_value;
	char	*var_name;

	if (name_len > 0)
	{
		var_name = _malloc(name_len + 1, 'm');
		ft_strncpy(var_name, &content[i - name_len], name_len);
		var_name[name_len] = '\0';
		var_value = expand_variable(g_mini.env, var_name);
		return (var_value);
	}
	return (NULL);
}
