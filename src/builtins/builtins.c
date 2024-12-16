/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/16 17:17:24 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins(t_env **env, t_cmd *command)
{
	pid_t	original_stdin;
	pid_t	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	set_redirections(command->files);
	if (strcmp("echo", command->cmd[0]) == 0)
		echo(command->cmd);
	else if (ft_strcmp("export", command->cmd[0]) == 0)
		export(env, command->cmd);
	else if (ft_strcmp("exit", command->cmd[0]) == 0)
		ft_exit(command);
	else if (ft_strcmp("cd", command->cmd[0]) == 0)
		cd(env, command->cmd);
	else if (ft_strcmp("pwd", command->cmd[0]) == 0)
		pwd(env);
	else if (ft_strcmp("env", command->cmd[0]) == 0)
		print_env(*env);
	else if (ft_strcmp("unset", command->cmd[0]) == 0)
		unset(command->cmd, env);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (1);
}
