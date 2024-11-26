/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/11/26 23:20:55 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins(t_env **env, t_list *lst)
{
	char	**arg = NULL;
	int i = 0;
	
	if (!lst)
		return 0;
	while (lst)
	{
		arg[i] = ft_strdup(lst->content);
		printf("content: %s\n", arg[i]);
		if (arg[0] == NULL)
			return (0);
		if (strcmp(arg[0], "export") == 0)
			export(arg, env);
		else if (strncmp("env", arg[0], 4) == 0)
			print_env(*env);
		else if (strcmp("pwd", arg[0]) == 0)
			pwd(env);
		else if (strcmp("echo", arg[0]) == 0)
			echo(arg);
		else if (strcmp(arg[0], "cd") == 0)
			cd(env, arg);
		else if (strcmp(arg[0], "unset") == 0)
			unset(arg, env);
		else if (strcmp(arg[0], "exit") == 0)
		{
			free(arg);
			exit(0);
		}
		else
			return (0);
		i++;
		lst = lst->next;
	}
		return (1);
}
