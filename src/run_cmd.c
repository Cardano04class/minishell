#include "minishell.h"

#define WRITE 1
#define READ 0

char	*ft_getenv(char *name, t_env *env)
{
	while(env != NULL)
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
	char 	*fullcmd;

	path = ft_getenv("PATH", env);
	if (path == NULL)
		return (cmd);
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
	return (NULL);
}

char	**convert_env(t_env *list_env)
{
	char	**env;
	int		env_size;
	int		j = 0;
	char 	*full_var;
	
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

void    execute(t_cmd *command, t_env *list_env)
{
	char	**env;
	pid_t	child_pid;
	int		status;
	char	*fullcmd;
	int 	fd_in = 0;
	int		fd_out = 1;
	// int 	std_in = dup(STDIN_FILENO);
	// int 	std_out = dup(STDOUT_FILENO);

    fullcmd = find_path(command->cmd[0], list_env);
		// puts("hna");
		//printf("commands file : %s\n", command->files->filename);
	if (fullcmd == NULL)
	{
		write(2, command->cmd[0], ft_strlen(command->cmd[0]));
		write(2, ": command not found\n", 20);
		return ;
	}
	env = convert_env(list_env);
	child_pid = fork();
	if (child_pid == 0)
	{
		while (command->files != NULL)
		{
			if (command->files->type == INRED)
			{
				fd_in = open(command->files->filename, O_RDONLY);
				printf("infile = %d\n", fd_in);
				if (fd_in == -1)
				{
					puts("infile ");
					perror(command->files->filename);
					exit(1);
				}
				if(dup2(fd_in, STDIN_FILENO) == -1)
				{
					perror(command->files->filename);
					exit(1);
				}
				close(fd_in);
			}
			if (command->files->type == OUTRED)
			{
				printf("out\n");
				fd_out = open(command->files->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				printf("outfile = %d\n", fd_out);
				if (fd_out == -1)
				{
					puts("outfile ");
					perror(command->files->filename);
					exit(1);
				}
				if(dup2(fd_out, STDOUT_FILENO) == -1)
				{
					perror(command->files->filename);
					exit(1);
				}
				close(fd_out);
			}
			if (command->files->type == APPEND)
			{
				printf("append\n");
				fd_out = open(command->files->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
				if (fd_out == -1)
				{
					puts("append ");
					perror(command->files->filename);
					exit(1);
				}
				if(dup2(fd_out, STDOUT_FILENO) == -1)
				{
					perror(command->files->filename);
					exit(1);
				}
				close(fd_out);
			}
			command->files = command->files->next;
		}
		if (execve(fullcmd, command->cmd, env) == -1)
		{
			perror(command->cmd[0]);
			exit(127);
		}
	}
	// close(fd_out);
	// close(fd_in);
	waitpid(child_pid, &status, 0);
}

void	handle_pipe(t_cmd *command, t_env *env)
{
	int		fd[2];
	pid_t 	child_pid1;
	pid_t	child_pid2;
	int 	status[2];
	
	if (pipe(fd) == -1)
		exit(1);
	//fd[READ] = fd --> READ mn lpipe
	//fd[WRITE] = fd --> WRITE mn lpipe
	child_pid1 = fork();
	if (child_pid1 == 0)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		execute(command, env);
		exit(1);
	}
	child_pid2 = fork();
	if (child_pid2 == 0)
	{
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		run_cmd(command->next, env);
		exit(1);
	}
	close(fd[READ]);
	close(fd[WRITE]);
	waitpid(child_pid1, &status[0], 0);
	waitpid(child_pid2, &status[1], 0);
}

void    run_cmd(t_cmd *command, t_env *env)
{
    if (command->next == NULL)
        execute(command, env);
	else
	{
		handle_pipe(command, env);
	}
}


// souwa 7louwa :