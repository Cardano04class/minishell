#include "minishell.h"

void run_heredoc(t_cmd	*command)
{
	char	*line;

	while (command->heredoc != NULL)
	{
		while (1)
		{
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