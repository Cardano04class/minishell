/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:49:46 by mamir             #+#    #+#             */
/*   Updated: 2024/11/13 15:09:18 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(t_env **env, const char *name, const char *value)
{
	t_env	*var;
	t_env	*new_var;

	var = find_env_var(*env, name);
	if (var)
	{
		free(var->value);
		var->value = strdup(value);
	}
	else
	{
		new_var = malloc(sizeof(t_env));
		if (!new_var)
		{
			perror("malloc");
			return ;
		}
		new_var->key = strdup(name);
		new_var->value = strdup(value);
		new_var->next = *env;
		*env = new_var;
	}
}

void	cd(t_env **env, char **args)
{
	t_env	*home_env;
	t_env	*oldpwd_env;
	t_env	*pwd_env;
	char	*home;
	char	cwd[1024];

	home_env = find_env_var(*env, "HOME");
	oldpwd_env = find_env_var(*env, "OLDPWD");
	pwd_env = find_env_var(*env, "PWD");
	if (home_env != NULL)
		home = home_env->value;
	else
		home = NULL;
	if (args[1] == NULL)
		cd_home(home);
	else if (strcmp(args[1], "-") == 0)
		cd_oldpwd(oldpwd_env);
	else
		cd_path(args[1]);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (pwd_env != NULL)
			update_env_var(env, "OLDPWD", pwd_env->value);
		update_env_var(env, "PWD", cwd);
	}
	else
		perror("cd: getcwd()");
}

void	pwd(t_env **env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		update_env_var(env, "PWD", cwd);
	}
	else
	{
		perror("pwd: getcwd() error");
	}
}
