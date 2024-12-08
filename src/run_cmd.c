#include "minishell.h"

#define WRITE 1
#define READ 0

char	*ft_getenv(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, name, ft_strlen(env->key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;
	int		j;
	char	*fullcmd;

	path = ft_getenv("PATH", env);
	if (path == NULL)
		return (cmd);
	if (cmd == NULL)
		return (NULL);
	//printf("cmd : %s\n", cmd);
	cmd = ft_strjoin("/", cmd);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	j = 0;
	while (paths[j] != NULL)
	{
		fullcmd = ft_strjoin(paths[j], cmd);
		if (access(fullcmd, F_OK) == 0)
			return (fullcmd);
		j++;
	}
	free (cmd);
	return (NULL);
}

char	**convert_env(t_env *list_env)
{
	char	**env;
	int		env_size;
	int		j;
	char	*full_var;

	j = 0;
	env_size = ft_envsize(list_env);
	env = malloc(sizeof(char *) * (env_size + 1));
	if (env == NULL)
		return (NULL);
	while (list_env != NULL && j < env_size)
	{
		full_var = ft_strjoin(list_env->key, "=");
		full_var = ft_strjoin(full_var, list_env->value);
		env[j] = full_var;
		j++;
		list_env = list_env->next;
	}
	env[j] = NULL;
	return (env);
}

bool	set_redirections(t_file *file)
{
	int	fd;

	while (file)
	{
		if (file->type == INRED || file->type == HEREDOC)
			fd = open(file->filename, O_RDONLY | O_CREAT, 0644);
		else if (file->type == OUTRED)
			fd = open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else if (file->type == APPEND)
			fd = open(file->filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (perror("minishell$"), false);
		if (file->type == INRED || file->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		file = file->next;
	}
	return (true);
}

int is_builtins(t_cmd *command)
{
    if (strcmp("echo", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("export", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("exit", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("cd", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("pwd", command->cmd[0]) == 0)
       return (1);
    else if (strcmp("env", command->cmd[0]) == 0)
        return (1);
    else if (strcmp("unset",command->cmd[0]) == 0)
        return (1);
    return (0);
}

int	execute_without_path(t_cmd *cmd)
{
	execve(cmd->cmd[0], cmd->cmd, convert_env(g_mini.env));
	perror("minishell$");
	exit(1);
}

int	execute_with_path(t_cmd *cmd)
{
	execvp(cmd->cmd[0], cmd->cmd);
	perror("minishell$");
	exit(1);
}

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		set_redirections(cmd->files);
		if (ft_strchr(cmd->cmd[0], '/') || !get_env(g_mini.env, "PATH")
			|| !*get_env(g_mini.env, "PATH"))
			execute_without_path(cmd);
		else
			execute_with_path(cmd);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	execute_str(t_cmd *cmd)
{
	g_mini.sig_flag = 1;
	if (is_builtins(cmd))
		run_builtins(&g_mini.env, cmd);
	else
		execute_cmd(cmd);
	return (0);
}

int	first_child(pid_t *pid, t_cmd *cmd, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		// sigexit
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_str(cmd);
		exit(1);
	}
	return (0);
}

int	second_child(pid_t *pid, t_cmd *cmd, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		// sigexit
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execution(cmd);
		exit(1);
	}
	return (0);
}

int	execute_pipe(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pids[2];


	pipe(fd);
	first_child(&pids[0], cmd, fd);
	second_child(&pids[1], cmd->next, fd);
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	return (0);
}

int	execution(t_cmd *cmd)
{
	if (cmd->next)
		execute_pipe(cmd);
	else
		execute_str(cmd);
	return (0);
}

// void	execute(t_cmd *command, t_env *list_env, t_env *env_list)
// {
// 	char	**env;
// 	pid_t	child_pid;
// 	int		status;
// 	char	*fullcmd = NULL;
// 	int 	fd_in = 0;
// 	int		fd_out = 1;
// 	// int 	std_in = dup(STDIN_FILENO);
// 	// int 	std_out = dup(STDOUT_FILENO);
// 	(void)env_list;


// 	if (command->cmd[0] == NULL)
// 	 return ;
// 	if (is_builtins(command) == 1)
// 	{
// 		run_builtins(&env_list, command);
// 		return ;
// 	}
// 	fullcmd = find_path(command->cmd[0], list_env);
// 	if (fullcmd == NULL)
// 	{
// 		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
// 		write(2, ": command not found\n", 20);
// 		g_mini.exit_status = 127;
// 		return ;
// 	}
// 	env = convert_env(list_env);
// 	child_pid = fork();
// 	if (child_pid == 0)
// 	{
// 		while (command->files != NULL)
// 		{
		
// 			if (command->files->type == INRED)
// 			{
// 				fd_in = open(command->files->filename, O_RDONLY);
// 				if (fd_in == -1)
// 				{
// 					perror(command->files->filename);
// 					exit(1);
// 				}
// 				if(dup2(fd_in, STDIN_FILENO) == -1)
// 				{
// 					perror(command->files->filename);
// 					exit(1);
// 				}
// 				close(fd_in);
// 			}
// 			if (command->files->type == OUTRED)
// 			{
// 				fd_out = open(command->files->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				if (fd_out == -1)
// 				{
// 					perror(command->files->filename);
// 					exit(1);
// 				}
// 				if(dup2(fd_out, STDOUT_FILENO) == -1)
// 				{
// 					perror(command->files->filename);
// 					exit(1);
// 				}
// 				close(fd_out);
// 			}
// 			if (command->files->type == APPEND)
// 			{
// 				fd_out = open(command->files->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 				if (fd_out == -1)
// 				{
// 					perror(command->files->filename);
// 					exit(1);
// 				}
// 				if(dup2(fd_out, STDOUT_FILENO) == -1)
// 				{
// 					perror(command->files->filename);
// 					exit(1);
// 				}
// 				close(fd_out);
// 			}
// 			if (command->files->type == HEREDOC)
// 			{
// 				fd_in = open(command->files->filename, O_RDONLY);
// 				if(dup2(fd_in, STDIN_FILENO) == -1)
// 				{
// 					//perror(command->files->filename);
// 					exit(1);
// 				}
// 				close(fd_in);
// 			}
// 			command->files = command->files->next;
// 		}
// 		if (execve(fullcmd, command->cmd, env) == -1)
// 		{
// 			perror(command->cmd[0]);
// 			exit(127);
// 		}
// 	}
// 	else 
// 	{
// 		waitpid(child_pid, &status, 0);

// 		g_mini.exit_status = capture_exit_status(status);
// 	}
// 	signal_handler(IN_CHILD);

// }

// void	handle_pipe(t_cmd *command, t_env *env, t_env *env_list)
// {
// 	int		fd[2];
// 	pid_t	child_pid1;
// 	pid_t	child_pid2;
// 	int		status[2];

// 	if (pipe(fd) == -1)
// 		exit(1);
// 	// fd[READ] = fd --> READ mn lpipe
// 	// fd[WRITE] = fd --> WRITE mn lpipe
// 	child_pid1 = fork();
// 	if (child_pid1 == 0)
// 	{
// 		close(fd[READ]);
// 		dup2(fd[WRITE], STDOUT_FILENO);
// 		close(fd[WRITE]);
// 		execute(command, env, env_list);
// 		exit(1);
// 	}
// 	child_pid2 = fork();
// 	if (child_pid2 == 0)
// 	{
// 		close(fd[WRITE]);
// 		dup2(fd[READ], STDIN_FILENO);
// 		close(fd[READ]);
// 		run_cmd(command->next, env, env_list);
// 		exit(1);
// 	}
// 	close(fd[READ]);
// 	close(fd[WRITE]);
// 	waitpid(child_pid1, &status[0], 0);
// 	waitpid(child_pid2, &status[1], 0);
// }


// void    run_cmd(t_cmd *command, t_env *env, t_env *env_list)
// {
	

// 	if (command->next == NULL)
//         execute(command, env, env_list);
// 	else
// 	{
// 		handle_pipe(command, env, env_list);
// 	}
// 	while (command->files != NULL)
// 	{
// 		if (command->files->type == HEREDOC && command->files->delimiter != NULL)
// 			unlink(command->files->filename);
// 		command->files = command->files->next;
// 	}
// }