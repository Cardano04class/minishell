/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:23:16 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 17:47:09 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_sorted_node(t_env **sorted_list, t_env *new_node)
{
	t_env	*prev;

	if (*sorted_list == NULL || ft_strcmp((*sorted_list)->key,
			new_node->key) > 0)
	{
		new_node->next = *sorted_list;
		*sorted_list = new_node;
		return ;
	}
	prev = *sorted_list;
	while (prev->next != NULL && ft_strcmp(prev->next->key, new_node->key) < 0)
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
		perror("Invalid Name");
		g_mini.exit_status = 1;
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
		var_name = ft_substr(str, 0, plus_sign);
	if (ft_strlen(var_value) == 0)
		var_value = ft_strdup("");
	result = validate_and_handle(lst, var_name, var_value, plus_sign);
	return (result);
}

t_env	*create_env_node(const t_env *current)
{
	t_env	*new_node;

	new_node = (t_env *)_malloc(sizeof(t_env), 'm');
	new_node->key = ft_strdup(current->key);
	if (current->value != NULL)
		new_node->value = ft_strdup(current->value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}
