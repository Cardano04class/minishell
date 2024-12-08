/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:46:42 by mamir             #+#    #+#             */
/*   Updated: 2024/12/08 16:01:12 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_variable(char *var_name, t_env **list)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *list;
	while (current)
	{
		if (ft_strcmp(var_name, current->key) == 0)
		{
			if (previous == NULL)
				*list = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

int	valid_name(char *name, t_env **list)
{
	t_env	*current;

	current = *list;
	while (current)
	{
		if (ft_strcmp(name, current->key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	unset(char **args, t_env **env_list)
{
	int		i;
	char	*var_name;

	if (args[1] == NULL)
		return (1);
	i = 1;
	while (args[i])
	{
		var_name = args[i];
		if (!env_exist(env_list, var_name))
			return 1;
		if (!valid_name(var_name, env_list))
			continue ;
		if (!remove_variable(var_name, env_list))
			return 1;
		i++;
	}
	return (0);
}
