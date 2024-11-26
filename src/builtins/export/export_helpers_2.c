/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:53:31 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 14:54:22 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(const t_env *current)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(current->key);
	if (current->value != NULL)
		new_node->value = ft_strdup(current->value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_exist(t_env **env_list, const char *name)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (strcmp(current->key, name) == 0)
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
			if (strcmp(current->key, name) == 0 && ft_strlen(current->key) != 0)
			{
				current->value = ft_strjoin(current->value, value);
				return ;
			}
		}
		else if (strcmp(current->key, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

t_env	*init_export_node(char *name)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Failed to allocate memory for new environment node");
		return (NULL);
	}
	new_node->key = ft_strdup(name);
	if (!new_node->key)
	{
		free(new_node);
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
			free(new_node->key);
			free(new_node);
			return (1);
		}
	}
	return (0);
}
