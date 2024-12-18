/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:01:50 by mamir             #+#    #+#             */
/*   Updated: 2024/12/16 23:31:07 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "_") != 0)
		{
			if (env->value == NULL)
				printf("declare -x %s\n", env->key);
			else if (ft_strlen(env->value) == 0)
				printf("declare -x %s=\"\"\n", env->key);
			else
				printf("declare -x %s=\"%s\"\n", env->key, env->value);
		}
		env = env->next;
	}
}

t_env	*set_env_var(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	if (!env || !key || !value)
		return (env);
	tmp = env;
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->value = ft_strdup(value);
	}
	return (env);
}

int	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (g_mini.default_env == NULL && (ft_strcmp(current->key,
					"PATH") == 0))
		{
			current = current->next;
			continue ;
		}
		if (current->value && *current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	g_mini.exit_status = 0;
	return (0);
}

void	ft_env(char **env, t_env **env_lst)
{
	t_env	*node;
	int		i;
	char	*equal_sign;

	i = 0;
	if (env != NULL && *env != NULL)
	{
		while (env[i])
		{
			equal_sign = ft_strchr(env[i], '=');
			if (equal_sign)
			{
				*equal_sign = '\0';
				node = ft_env_new(env[i], equal_sign + 1);
				*equal_sign = '=';
				if (node)
					ft_env_addback(env_lst, node);
			}
			i++;
		}
	}
	else
		create_env(env_lst);
}
