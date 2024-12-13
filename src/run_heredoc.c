#include "minishell.h"

char	*heredoc_filename(void)
{
	char	*file_name;
	char	line[2];
	int		fd;
	int		c;

	file_name = _malloc(sizeof(char) * 12, 'm');
	if (file_name == NULL)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	c = 0;
	while (c < 11)
	{
		read(fd, line, 1);
		if (ft_isalpha(line[0]))
			file_name[c++] = line[0];
	}
	file_name[c] = '\0';
	close(fd);
	return (file_name);
}

void run_heredoc(t_cmd	*command)
{
	char	*line;
	pid_t	child_pid;
	int		status;
	int		fd;

	fd = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		while (command->files != NULL)
		{
			if (command->files->type == HEREDOC)
			{
				fd = open(command->files->filename, O_WRONLY | O_CREAT, 0777);
				if (fd == -1)
					exit(1);
				while (1)
				{
					signal_handler(IN_HEREDOC);
					line = readline(">");
					if (line == NULL)
					{
						printf("warning : delimited by end-of-file (wanted `%s')\n", command->files->delimiter);
						break ;
					}
					if (!ft_strncmp(command->files->delimiter, line, 
						ft_strlen(command->files->delimiter)) &&
						(ft_strlen(command->files->delimiter) == ft_strlen(line)))
						{
							break ;
						}
					/*if (ft_strchr(line, '$') != NULL)
					{
						line = expand_variables(g_mini.env, line);
						write(fd, line, ft_strlen(line));
						write(fd, "\n", 1);
					}*/
					else
					{
						write(fd, line, ft_strlen(line));
						write(fd, "\n", 1);
					}
				}
			}
			command->files = command->files->next;
		}
		close(fd);
		exit(0);
	}
	waitpid(child_pid, &status, 0);
}
