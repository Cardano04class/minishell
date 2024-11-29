#include "minishell.h"

void run_heredoc(t_cmd	*command)
{
	char	*line;
	pid_t	child_pid;
	int		status;
	int		fd;
	char *file = "/tmp/heredoc.txt";

	child_pid = fork();
	if (child_pid == 0)
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 644);
		if (fd == -1)
			exit(1);
		while (command->heredoc != NULL)
		{
			while (1)
			{
				signal_handler(IN_HEREDOC);
				line = readline(">");
				if (!ft_strncmp(command->heredoc->delimiter, line, 
					ft_strlen(command->heredoc->delimiter)) &&
					(ft_strlen(command->heredoc->delimiter) == ft_strlen(line)))
					{
						break ;
					}
				else
				{
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
				}
			}
			command->heredoc = command->heredoc->next;
		}
		exit(0);
	}
	waitpid(child_pid, &status, 0);
	g_mini.heredoc_fd = open(file, O_CREAT | O_RDWR, 644);
}