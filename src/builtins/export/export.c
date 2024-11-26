/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:44:51 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_export_node(t_env **env_lst, char *name, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = init_export_node(name);
	if (!new_node)
		return (NULL);
	if (set_node_value(new_node, value))
		return (NULL);
	if (*env_lst == NULL)
		*env_lst = new_node;
	else
	{
		current = *env_lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (new_node);
}

int	handle_existing_node(t_env **lst, char *var_name, char *var_value,
		int plus_sign)
{
	t_env	*existing_node;

	existing_node = env_exist(lst, var_name);
	if (existing_node)
	{
		if (plus_sign != -1)
			update_env(lst, var_name, var_value, true);
		else
			update_env(lst, var_name, var_value, false);
	}
	else if (!ft_export_node(lst, var_name, var_value))
	{
		perror("Error setting variable:");
		free(var_name);
		free(var_value);
		return (1);
	}
	return (0);
}

static int	handle_no_equal_sign(t_env **lst, char *str)
{
	char	*var_name;
	t_env	*existing_node;

	var_name = ft_strdup(str);
	if (!is_valid_name(var_name))
	{
		printf("export: '%s': not a valid identifier\n", var_name);
		free(var_name);
		return (1);
	}
	existing_node = env_exist(lst, var_name);
	if (!existing_node && !ft_export_node(lst, var_name, NULL))
	{
		perror("failed adding variable\n");
		free(var_name);
		return (1);
	}
	free(var_name);
	return (0);
}

int	set_env(t_env **lst, char *str)
{
	int	equal_sign;
	int	plus_sign;

	equal_sign = find_equals(str);
	plus_sign = find_plus(str);
	if (equal_sign == -1)
		return (handle_no_equal_sign(lst, str));
	return (handle_equal_sign(lst, str, equal_sign, plus_sign));
}

int	export(char **args, t_env **lst)
{
	int		i;
	t_env	*sorted;

	sorted = NULL;
	if (args[1] == NULL)
	{
		sorted = sort_env(*lst);
		print_export(sorted);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		set_env(lst, args[i]);
		i++;
	}
	return (0);
}
