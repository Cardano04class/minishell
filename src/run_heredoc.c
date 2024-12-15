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
char	*find_var_value(t_env *env, const char *var_name)
{
	t_env	*current;
	current = env;

	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

char *expand_in_heredoc(t_env *env, char *content)
{
    int i = 0, 
	expanded_len = 0;

    while (content[i])
    {
        if (content[i] == '$')
        {
            i++;
            if (content[i] == '\0')
            {
                expanded_len++;
                continue;
            }
            if (content[i] == '?')
            {
                char *exit_status = ft_itoa(g_mini.exit_status);
                if (exit_status)
                {
                    expanded_len += strlen(exit_status);
                }
                i++;
                continue;
            }
            int name_len = 0;
            while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
            {
                name_len++;
                i++;
            }
            if (name_len > 0)
            {
                char *var_name = _malloc(name_len + 1, 'm');
                ft_strncpy(var_name, &content[i - name_len], name_len);
                var_name[name_len] = '\0';

                char *var_value = find_var_value(env, var_name);
                if (var_value)
                {
                    expanded_len += ft_strlen(var_value);
                }
            }
        }
        else
        {
            expanded_len++;
            i++;
        }
    }
    char *expanded_content = _malloc(expanded_len + 1, 'm');
    i = 0;
    int j = 0;

    while (content[i])
    {
        if (content[i] == '$')
        {
            i++;
            if (content[i] == '\0' || content[i] == '"' || content[i] == '\'') 
            {
                expanded_content[j++] = '$';
                continue;
            }
            if (content[i] == '?')
            {
                char *exit_status = ft_itoa(g_mini.exit_status);
                if (exit_status)
                {
                    int status_len = ft_strlen(exit_status);
                    ft_strcpy(&expanded_content[j], exit_status);
                    j += status_len;
                }
                i++;
                continue;
            }
            int name_len = 0;
            while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
            {
                name_len++;
                i++;
            }
            if (name_len > 0)
            {
                char *var_name = _malloc(name_len + 1, 'm');
                ft_strncpy(var_name, &content[i - name_len], name_len);
                var_name[name_len] = '\0';
                char *var_value = expand_variable(env, var_name);
                if (var_value)
                {
                    int value_len = ft_strlen(var_value);
                    ft_strcpy(&expanded_content[j], var_value);
                    j += value_len;
                }
            }
        }
        else
        {
            expanded_content[j++] = content[i++];
        }
    }
    expanded_content[j] = '\0';
    return expanded_content;
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
					if (ft_strchr(line, '$') != NULL)
					{
						line = expand_in_heredoc(g_mini.env, line);
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
