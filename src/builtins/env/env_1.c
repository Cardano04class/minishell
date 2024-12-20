/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:33:09 by mamir             #+#    #+#             */
/*   Updated: 2024/12/16 23:40:05 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env(t_env **env_list)
{
	const char	*path;
	char		*underscore;

	path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	underscore = "/usr/bin/env";
	ft_env_addback(env_list, ft_env_new("PWD", getcwd(NULL, 0)));
	ft_env_addback(env_list, ft_env_new("OLDPWD", ft_strdup("")));
	ft_env_addback(env_list, ft_env_new("PATH", ft_strdup(path)));
	ft_env_addback(env_list, ft_env_new("SHLVL", ft_strdup("1")));
	ft_env_addback(env_list, ft_env_new("_", underscore));
	return (*env_list);
}
