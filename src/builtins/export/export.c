/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:38:20 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 18:00:49 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_no_equal_sign(t_env **env_list, char *str)
{
	char	*var_name;
	t_env	*existing_node;

	var_name = ft_strdup(str);
	if (!is_valid_name(var_name))
	{
		printf("export: not a valid identifier\n");
		g_mini.exit_status = 1;
		return (1);
	}
	existing_node = env_exist(env_list, var_name);
	if (!existing_node && !ft_export_node(env_list, var_name, NULL))
	{
		perror("failed adding variable\n");
		g_mini.exit_status = 1;
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
	int		status;

	status = 0;
	sorted = NULL;
	if (args[1] == NULL)
	{
		sorted = sort_env(*env_list);
		print_export(sorted);
		g_mini.exit_status = 0;
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (set_env(env_list, args[i]) != 0)
			status = 1;
		i++;
	}
	g_mini.exit_status = status;
	return (0);
}
