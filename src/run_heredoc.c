#include "minishell.h"

void run_heredoc(t_cmd	*command)
{
	char	*line;
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == 0)
	{
		while (command->heredoc != NULL)
		{
			while (1)
			{
				signal_handler(IN_CHILD);
				line = readline(">");
				if (!ft_strncmp(command->heredoc->delimiter, line, 
					ft_strlen(command->heredoc->delimiter)) &&
					(ft_strlen(command->heredoc->delimiter) == ft_strlen(line)))
					{
						// printf("%d\n", ft_strlen(command->heredoc->delimiter));
						break ;
					}
			}
			command->heredoc = command->heredoc->next;
		}
	}
	waitpid(child_pid, &status, 0);
}