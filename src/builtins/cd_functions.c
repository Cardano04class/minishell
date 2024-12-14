/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:49:03 by mamir             #+#    #+#             */
/*   Updated: 2024/12/14 23:25:12 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home(char *home)
{
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_mini.exit_status = 1;
		return ;
	}
	if (chdir(home) != 0)
		perror("cd");
	else
		g_mini.exit_status = 0;
}

void	cd_oldpwd(t_env *oldpwd_env)
{
	if (oldpwd_env != NULL && oldpwd_env->value != NULL)
	{
		if (chdir(oldpwd_env->value) == 0)
		{
			printf("%s\n", oldpwd_env->value);
		}
		else
		{
			g_mini.exit_status = 1;
			perror("cd");
		}
	}
	else
	{
		g_mini.exit_status = 1;
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
	}
}

void	cd_path(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
	}
	else
		g_mini.exit_status = 0;
}

void	update_pwd_env(t_env **env, t_env *pwd_env, char *cwd)
{
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (pwd_env != NULL)
			update_env_var(env, "OLDPWD", pwd_env->value);
		update_env_var(env, "PWD", cwd);
	}
	else
		perror("cd: getcwd");
}

t_env	*find_env_var(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
