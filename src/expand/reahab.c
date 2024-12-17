char	*remove_quotes_and_expand(t_env *env, char *content)
{
	int		i;
	int		expanded_len;
	int		in_single_quote;
	int		in_double_quote;
	char	*exit_status;
	int		name_len;
	char	*var_name;
	char	*var_value;
	char	*expanded_content;
	int		j;
	int		status_len;
	int		value_len;

	i = 0;
	expanded_len = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (content[i])
	{
		if (content[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			if (in_single_quote)
				i++;
			continue ;
		}
		if (content[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			if (in_double_quote)
				i++;
			continue ;
		}
		if (content[i] == '$' && !in_single_quote)
		{
			i++;
			if (content[i] == '\0')
			{
				expanded_len++;
				continue ;
			}
			if (content[i] == '?')
			{
				exit_status = ft_itoa(g_mini.exit_status);
				if (exit_status)
				{
					expanded_len += strlen(exit_status);
				}
				i++;
				continue ;
			}
			name_len = 0;
			while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
			{
				name_len++;
				i++;
			}
			if (name_len > 0)
			{
				var_name = _malloc(name_len + 1, 'm');
				ft_strncpy(var_name, &content[i - name_len], name_len);
				var_name[name_len] = '\0';
				var_value = expand_variable(env, var_name);
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
	expanded_content = _malloc(expanded_len + 1, 'm');
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (content[i])
	{
		if (content[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			if (in_single_quote)
				i++;
			continue ;
		}
		if (content[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			if (in_double_quote)
				i++;
			continue ;
		}
		if (content[i] == '$' && !in_single_quote)
		{
			i++;
			if (content[i] == '\0' || content[i] == '"' || content[i] == '\'')
			{
				expanded_content[j++] = '$';
				continue ;
			}
			if (content[i] == '?')
			{
				exit_status = ft_itoa(g_mini.exit_status);
				if (exit_status)
				{
					status_len = ft_strlen(exit_status);
					ft_strcpy(&expanded_content[j], exit_status);
					j += status_len;
				}
				i++;
				continue ;
			}
			name_len = 0;
			while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
			{
				name_len++;
				i++;
			}
			if (name_len > 0)
			{
				var_name = _malloc(name_len + 1, 'm');
				ft_strncpy(var_name, &content[i - name_len], name_len);
				var_name[name_len] = '\0';
				var_value = expand_variable(env, var_name);
				if (var_value)
				{
					value_len = ft_strlen(var_value);
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
	return (expanded_content);
}
