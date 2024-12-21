/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:35:12 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/21 10:57:36 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_without_path(t_cmd *command)
{
	if (access(command->cmd[0], F_OK) != 0)
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": No such file or directory\n", 28);
		g_mini.exit_status = 127;
		_malloc(0, 'f');
		exit(g_mini.exit_status);
	}
	if_executable(command->cmd[0]);
	execve(command->cmd[0], command->cmd, convert_env(g_mini.env));
	perror("without path");
	_malloc(0, 'f');
	exit(1);
}

int	execute_with_path(t_cmd *command)
{
	char	**env;
	char	*fullcmd;

	env = NULL;
	fullcmd = NULL;
	fullcmd = find_path(command->cmd[0], g_mini.env);
	if (fullcmd == NULL || command->cmd[0][0] == '\0')
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 20);
		_malloc(0, 'f');
		g_mini.exit_status = 127;
		exit(g_mini.exit_status);
	}
	if_executable(fullcmd);
	env = convert_env(g_mini.env);
	execve(fullcmd, command->cmd, env);
	perror("with path:");
	_malloc(0, 'f');
	g_mini.exit_status = 2;
	exit(g_mini.exit_status);
}

int	run_command(t_cmd *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		check_if_cmd_valid(command);
		signal(SIGQUIT, SIG_DFL);
		set_redirections(command->files, command);
		if (ft_strchr(command->cmd[0], '/') || !get_env(g_mini.env, "PATH")
			|| !*get_env(g_mini.env, "PATH"))
			execute_without_path(command);
		else
			execute_with_path(command);
	}
	waitpid(pid, &status, 0);
	g_mini.exit_status = capture_exit_status(status);
	return (g_mini.exit_status);
}

int	run_builtins(t_env **env, t_cmd *command)
{
	pid_t	original_stdin;
	pid_t	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	set_redirections(command->files, command);
	if (ft_strcmp("echo", command->cmd[0]) == 0)
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

int	execute_command(t_cmd *command)
{
	pid_t	original_stdin;
	pid_t	original_stdout;

	g_mini.sig_flag = 1;
	if (command->cmd[0] != NULL)
	{
		if (is_builtins(command))
			run_builtins(&g_mini.env, command);
		else
			run_command(command);
	}
	else if (command->cmd[0] == NULL && command->files != NULL)
	{
		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup(STDOUT_FILENO);
		set_redirections(command->files, command);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
	return (0);
}
