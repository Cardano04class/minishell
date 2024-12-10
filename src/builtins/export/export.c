/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/12/08 22:31:07 by mamir            ###   ########.fr       */
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
		perror("Invalid Name");
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
		
		var_name = ft_substr(str, 0, plus_sign);
	}
	if (ft_strlen(var_value) == 0)
	{
		
		var_value = ft_strdup("");
	}
	result = validate_and_handle(lst, var_name, var_value, plus_sign);
	
	
	return (result);
}


t_env	*create_env_node(const t_env *current)
{
	t_env	*new_node;

	new_node = (t_env *)_malloc(sizeof(t_env), 'm');
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
			if (ft_strcmp(current->key, name) == 0 && ft_strlen(current->key) != 0)
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
		return (NULL);
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

int	handle_no_equal_sign(t_env **env_list, char *str)
{
	char	*var_name;
	t_env	*existing_node;

	var_name = ft_strdup(str);
	if (!is_valid_name(var_name))
	{
		printf("export: '%s': not a valid identifier\n", var_name);
		
		return (1);
	}
	existing_node = env_exist(env_list, var_name);
	if (!existing_node && !ft_export_node(env_list, var_name, NULL))
	{
		perror("failed adding variable\n");
		
		return (1);
	}
	
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

int	export(t_env **env_list, char **args)
{
	int		i;
	t_env	*sorted;

	sorted = NULL;
	if (args[1] == NULL)
	{
		sorted = sort_env(*env_list);
		print_export(sorted);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		set_env(env_list, args[i]);
		i++;
	}
	return (0);
}
