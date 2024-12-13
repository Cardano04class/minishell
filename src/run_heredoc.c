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
char *expand_heredoc_variable(t_env *env, const char *var_name)
{
    t_env *current = env;

    while (current)
    {
        if (strcmp(current->key, var_name) == 0)
        {
            printf("test %s\n", current->value);
            return current->value;  // Return the value of the variable if found
        }
        current = current->next;
    }

    return NULL;  // Return NULL if the variable is not found
}

char *heredoc_expand(t_env *env, char *content)
{
    char expanded_content[1024] = {0};
    int i = 0; 
	int	j = 0;

    while (content[i] != '\0')
    {
        if (content[i] == '$')
        {
            i++; 
            if (content[i] == '\0')
            {
                expanded_content[j++] = '$';
                continue;
            }

            char var_name[256] = {0};
            int name_idx = 0;

            while (content[i] != '\0' && (ft_isalnum(content[i]) || content[i] == '_'))
                var_name[name_idx++] = content[i++];
            var_name[name_idx] = '\0';

            char *var_value = expand_heredoc_variable(env, var_name);
            if (var_value)
            {
                int k = 0;
                while (var_value[k])
                    expanded_content[j++] = var_value[k++];
            }
        }
        else
        {
            expanded_content[j++] = content[i++];
        }
    }

    expanded_content[j] = '\0';
    return strdup(expanded_content);
}

void run_heredoc(t_cmd	*command)
{
	char	*line;
	pid_t	child_pid;
	int		status;
	int		fd;
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
					//int	i = 0;
					if (ft_strchr(line, '$') != NULL)
					{
						line = heredoc_expand(g_mini.env, line);
						printf("|line : %s |\n", line);
						write(fd, line, ft_strlen(line));
						write(fd, "\n", 1);
					}
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
	g_mini.exit_status = capture_exit_status(status);
}

/*
		if varible not found, print new line. Example: ($dd).

 */