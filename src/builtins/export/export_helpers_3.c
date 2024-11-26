/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:56:41 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:02:08 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_sorted_node(t_env **sorted_list, t_env *new_node)
{
	t_env	*prev;

	if (*sorted_list == NULL || strcmp((*sorted_list)->key, new_node->key) > 0)
	{
		new_node->next = *sorted_list;
		*sorted_list = new_node;
		return ;
	}
	prev = *sorted_list;
	while (prev->next != NULL && strcmp(prev->next->key, new_node->key) < 0)
		prev = prev->next;
	new_node->next = prev->next;
	prev->next = new_node;
}

t_env	*sort_env(const t_env *env_list)
{
	t_env		*sorted_list;
	const t_env	*current;
	t_env		*new_node;

	sorted_list = NULL;
	current = env_list;
	while (current != NULL)
	{
		new_node = create_env_node(current);
		if (!new_node)
			return (NULL);
		insert_sorted_node(&sorted_list, new_node);
		current = current->next;
	}
	return (sorted_list);
}

int	validate_and_handle(t_env **lst, char *var_name, char *var_value,
	int plus_sign)
{
	int	result;

	if (!is_valid_name(var_name))
	{
		printf("export: '%s': not a valid identifier\n", var_name);
		return (1);
	}
	result = handle_existing_node(lst, var_name, var_value, plus_sign);
	return (result);
}

int	handle_equal_sign(t_env **lst, char *str, int equal_sign, int plus_sign)
{
	char	*var_name;
	char	*var_value;
	int		result;

	var_name = ft_substr(str, 0, equal_sign);
	var_value = ft_substr(str, equal_sign + 1, ft_strlen(str) - equal_sign - 1);
	if (plus_sign != -1)
	{
		free(var_name);
		var_name = ft_substr(str, 0, plus_sign);
	}
	if (ft_strlen(var_value) == 0)
	{
		free(var_value);
		var_value = ft_strdup("");
	}
	result = validate_and_handle(lst, var_name, var_value, plus_sign);
	free(var_name);
	free(var_value);
	return (result);
}
