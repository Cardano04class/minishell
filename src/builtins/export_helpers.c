/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:42:57 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 14:57:48 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (strcmp(lst->key, lst->next->key) > 0)
			return (1);
		if (strcmp(lst->key, lst->next->key) < 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}
