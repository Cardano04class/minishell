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
	if (i > 0)
	{
		while (env != NULL)
		{
			if (ft_strcmp(env->key, name) == 0)
				env->value = ft_strdup(cmd_argv[i]);
			env = env->next;
		}
	}
	return NULL;
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
	env = _malloc(sizeof(char *) * (env_size + 1), 'm');
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

void if_executable(char *str)
{
    if (access(str, X_OK) != 0) 
	{
        write(2, str, ft_strlen(str));
        write(2, ": Permission denied\n", 20);
        g_mini.exit_status = 126;
        exit(g_mini.exit_status);
    }
}

int	execute_without_path(t_cmd *command)
{
	if (access(command->cmd[0], F_OK) != 0) 
	{
        write(2, command->cmd[0], ft_strlen(command->cmd[0]));
        write(2, ": No such file or directory\n", 28);
        g_mini.exit_status = 127;
        exit(g_mini.exit_status);
    }
	if_executable(command->cmd[0]);
	ft_dashcase("_");
	execve(command->cmd[0], command->cmd, convert_env(g_mini.env));
	perror("minishell$");
	exit(1);
}

int	execute_with_path(t_cmd *command)
{
	char	**env;
	char	*fullcmd;
	
	env = NULL;
	fullcmd = NULL;
	fullcmd = find_path(command->cmd[0], g_mini.env);
	if (fullcmd == NULL)
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 20);
		g_mini.exit_status = 127;
		exit (g_mini.exit_status);
	}
	if_executable(fullcmd);
	env = convert_env(g_mini.env);
	ft_dashcase("_");
	execve(fullcmd, command->cmd, env);
	perror("minishell$");
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
		signal(SIGQUIT, SIG_DFL);
		set_redirections(command->files);
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

int	execute_command(t_cmd *command)
{
	g_mini.sig_flag = 1;
	if (is_builtins(command))
		run_builtins(&g_mini.env, command);
	else
		run_command(command);
	return (0);
}

int	first_child(pid_t *pid, t_cmd *command, int *fd)
{
	*pid = fork();
	if (*pid == 0)
	{
		// sigexit
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
	struct stat path_stat;

	//printf("command->cmd[0] : %s\n", command->cmd[0]);
    if (stat(command->cmd[0], &path_stat) == 0 
		&& S_ISDIR(path_stat.st_mode)) 
	{
        write(2, "minishell: ", 12);
        write(2, command->cmd[0], ft_strlen(command->cmd[0]));
        write(2, ": Is a directory\n", 17);
        g_mini.exit_status = 126;
        return (1);
    }
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
