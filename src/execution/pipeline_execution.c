/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:35:32 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:02:57 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

int	first_child(pid_t *pid, t_cmd *command, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(command);
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
	ft_dashcase("_");
	check_if_cmd_valid(command);
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
