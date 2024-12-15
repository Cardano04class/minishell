/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:23:53 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 18:02:53 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_exist(t_env **env_list, const char *name)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_env(t_env **env_list, char *name, char *value, bool plus_sign)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (plus_sign == true)
		{
			if (ft_strcmp(current->key, name) == 0
				&& ft_strlen(current->key) != 0)
			{
				current->value = ft_strjoin(current->value, value);
				return ;
			}
		}
		else if (ft_strcmp(current->key, name) == 0)
		{
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

t_env	*init_export_node(char *name)
{
	t_env	*new_node;

	new_node = (t_env *)_malloc(sizeof(t_env), 'm');
	if (!new_node)
	{
		perror("failed init variable");
		return (NULL);
	}
	new_node->key = ft_strdup(name);
	if (!new_node->key)
	{
		return (NULL);
	}
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	set_node_value(t_env *new_node, char *value)
{
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			return (1);
		}
	}
	return (0);
}

int	is_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
