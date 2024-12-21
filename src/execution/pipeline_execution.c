/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:35:32 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/21 01:04:12 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

t_env	*ft_dashcase(char *name)
{
	int		i;
	t_env	*env;
	char	**cmd_argv;

	i = 0;
	env = g_mini.env;
	cmd_argv = g_mini.command->cmd;
	while (cmd_argv[i + 1] != NULL)
		i++;
	if (i >= 0)
	{
		while (env != NULL)
		{
			if (ft_strcmp(env->key, name) == 0)
				env->value = ft_strdup(cmd_argv[i]);
			env = env->next;
		}
	}
	return (NULL);
}

int	first_child(pid_t *pid, t_cmd *command, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(command);
		_malloc(0, 'f');
		exit(g_mini.exit_status);
	}
	return (0);
}

int	second_child(pid_t *pid, t_cmd *command, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execution(command);
		_malloc(0, 'f');
		exit(g_mini.exit_status);
	}
	return (0);
}

int	execute_pipe(t_cmd *command)
{
	int		fd[2];
	pid_t	pids[2];
	int		status;

	pipe(fd);
	first_child(&pids[0], command, fd);
	second_child(&pids[1], command->next, fd);
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pids[0], &status, 0);
	waitpid(pids[1], &status, 0);
	g_mini.exit_status = capture_exit_status(status);
	return (0);
}

int	execution(t_cmd *command)
{
	if (command->cmd[0] != NULL)
		ft_dashcase("_");
	if (command->next)
	{
		g_mini.exit_pipe = 1;
		execute_pipe(command);
	}
	else
		execute_command(command);
	g_mini.exit_pipe = 0;
	return (0);
}
