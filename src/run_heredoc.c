/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:51:02 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/17 17:10:06 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	char_is_null(char i_content, int *expanded_len)
{
	if (i_content == '\0')
		return (*expanded_len = *expanded_len + 1);
	return (0);
}

int	char_is_exit_holder(char i_content, int *expanded_len, int *i)
{
	char	*exit_status;

	if (i_content == '?')
	{
		*i = *i + 1;
		exit_status = ft_itoa(g_mini.exit_status);
		if (exit_status != NULL)
			*expanded_len += strlen(exit_status);
		return (1);
	}
	return (0);
}

int	get_var_name_length(char *content, int *i)
{
	int	name_len;

	name_len = 0;
	while (content[*i] && (ft_isalnum(content[*i]) || content[*i] == '_'))
	{
		name_len++;
		*i = *i + 1;
	}
	return (name_len);
}

int	get_var_value_length(char *content, int name_len, int i)
{
	char	*var_name;
	char	*var_value;
	int		expanded_len;

	expanded_len = 0;
	var_name = _malloc(name_len + 1, 'm');
	ft_strncpy(var_name, &content[i - name_len], name_len);
	var_name[name_len] = '\0';
	var_value = find_var_value(g_mini.env, var_name);
	if (var_value != NULL)
		expanded_len += ft_strlen(var_value);
	return (expanded_len);
}

int	calculate_var_expansion_length(char *content)
{
	int	i;
	int	expanded_len;
	int	name_len;

	i = 0;
	expanded_len = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '$')
		{
			i++;
			if (char_is_null(content[i], &expanded_len)
				|| char_is_exit_holder(content[i], &expanded_len, &i))
				continue ;
			name_len = get_var_name_length(content, &i);
			if (name_len > 0)
				expanded_len += get_var_value_length(content, name_len, i);
		}
		else
		{
			expanded_len++;
			i++;
		}
	}
	return (expanded_len);
}

int	char_is_null_fill(char i_content, char **expanded_content, int *j)
{
	if (i_content == '\0')
	{
		(*expanded_content[*j]) = '$';
		*j += 1;
		return (1);
	}
	return (0);
}

int	char_is_exit_holder_fill(char i_content, char **expanded_content, int *i,
		int *j)
{
	char	*exit_status;
	int		status_len;

	if (i_content == '?')
	{
		exit_status = ft_itoa(g_mini.exit_status);
		if (exit_status != NULL)
		{
			status_len = ft_strlen(exit_status);
			ft_strcpy(*expanded_content + *j, exit_status);
			*j = *j + status_len;
			printf("j :  %i\n", *j);
		}
		*i += 1;
		return (1);
	}
	return (0);
}

char	*get_var_value(char *content, int name_len, int i)
{
	char	*var_value;
	char	*var_name;

	if (name_len > 0)
	{
		var_name = _malloc(name_len + 1, 'm');
		ft_strncpy(var_name, &content[i - name_len], name_len);
		var_name[name_len] = '\0';
		var_value = expand_variable(g_mini.env, var_name);
		return (var_value);
	}
	return (NULL);
}

void	fill_expanded_content(char *var_value, char **expanded_content, int *j)
{
	int	value_len;

	if (var_value != NULL)
	{
		value_len = ft_strlen(var_value);
		ft_strcpy(*expanded_content + *j, var_value);
		*j += value_len;
	}
}

char	*copy_expanded_content(char *content, int expanded_len)
{
	char	*expanded_content;

	int (i), (j), (name_len);
	i = 0;
	j = 0;
	expanded_content = _malloc(expanded_len + 1, 'm');
	while (content[i] != '\0')
	{
		if (content[i] == '$')
		{
			i++;
			if (char_is_null_fill(content[i], &expanded_content, &j)
				|| char_is_exit_holder_fill(content[i], &expanded_content, &i,
					&j))
				continue ;
			name_len = get_var_name_length(content, &i);
			if (name_len > 0)
				fill_expanded_content(get_var_value(content, name_len, i),
					&expanded_content, &j);
		}
		else
			expanded_content[j++] = content[i++];
	}
	return (expanded_content[j] = '\0', expanded_content);
}

char	*expand_in_heredoc(char *content)
{
	int		expanded_len;
	char	*expanded_content;

	expanded_len = calculate_var_expansion_length(content);
	expanded_content = copy_expanded_content(content, expanded_len);
	return (expanded_content);
}

static void	write_line_fd(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	heredoc_line_handler(t_cmd *command, int fd)
{
	char	*line;

	while (1)
	{
		signal_handler(IN_HEREDOC);
		line = readline(">");
		if (line == NULL)
		{
			printf("warning : delimited by end-of-file (wanted `%s')\n",
				command->files->delimiter);
			break ;
		}
		if (!ft_strcmp(command->files->delimiter, line))
			break ;
		if (ft_strchr(line, '$') != NULL)
		{
			line = expand_in_heredoc(line);
			write_line_fd(line, fd);
		}
		else
			write_line_fd(line, fd);
	}
	return (fd);
}

void	run_heredoc(t_cmd *command)
{
	int		fd;
	int		status;
	pid_t	child_pid;

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
				heredoc_line_handler(command, fd);
			}
			command->files = command->files->next;
		}
		close(fd);
		exit(0);
	}
	waitpid(child_pid, &status, 0);
	g_mini.exit_status = capture_exit_status(status);
}
