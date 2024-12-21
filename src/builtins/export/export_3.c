/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:24:50 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 17:59:30 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] == '=' && str[i] == '+')
			return (i);
		i++;
	}
	return (-1);
}

int	find_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	already_sorted(t_env *lst)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, lst->next->key) > 0)
			return (1);
		if (ft_strcmp(lst->key, lst->next->key) < 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

t_env	*ft_export_node(t_env **env_env_list, char *name, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = init_export_node(name);
	if (!new_node)
		return (NULL);
	if (set_node_value(new_node, value))
	{
		return (NULL);
	}
	if (*env_env_list == NULL)
		*env_env_list = new_node;
	else
	{
		current = *env_env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (new_node);
}

int	handle_existing_node(t_env **env_list, char *var_name, char *var_value,
		int plus_sign)
{
	t_env	*existing_node;

	existing_node = env_exist(env_list, var_name);
	if (existing_node)
	{
		if (plus_sign != -1)
			update_env(env_list, var_name, var_value, true);
		else
			update_env(env_list, var_name, var_value, false);
	}
	else if (!ft_export_node(env_list, var_name, var_value))
	{
		perror("Error setting variable:");
		return (1);
	}
	return (0);
}
