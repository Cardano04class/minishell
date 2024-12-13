/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_re.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:48 by mamir             #+#    #+#             */
/*   Updated: 2024/12/13 22:42:16 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}


char	*expand_variable(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (ft_strdup(""));
}

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*handle_special_vars(t_env *env, char *var_name)
{
	if (ft_strcmp(var_name, "?") == 0)
	{
		return (ft_itoa(g_mini.exit_status));
	}
	return (expand_variable(env, var_name));
}

static char	*extract_var_name(const char *content, int *i)
{
	size_t	name_len;
	char	*var_name;

	name_len = 0;
	while (content[*i + name_len] && is_valid_var_char(content[*i + name_len]))
		name_len++;
	var_name = _malloc(name_len + 1, 'm');
	ft_strncpy(var_name, &content[*i], name_len);
	var_name[name_len] = '\0';
	*i += name_len;
	return (var_name);
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	*remove_quotes_and_expand(t_env *env, char *content)
{
	char	*expanded;
	int		i;
	int		j;
	char	current_quote;
	char	*var_name;
	char	*var_value;
	int		content_len;
	int		quote_removal_mode;

	content_len = ft_strlen(content);
	expanded = _malloc(content_len * 2 + 1, 'm');
	if (!expanded)
		return (NULL);

	i = 0;
	j = 0;
	current_quote = '\0';
	quote_removal_mode = 0;

	// Detect if entire string is enclosed in same type of quotes
	if (content_len >= 2 && 
		content[0] == content[content_len - 1] && 
		is_quote(content[0]))
	{
		quote_removal_mode = 1;
	}

	while (content[i])
	{
		if (is_quote(content[i]))
		{
			if (current_quote == '\0')
			{
				current_quote = content[i];
				if (quote_removal_mode && current_quote == content[0])
				{
					i++;
					continue;
				}
			}
			else if (current_quote == content[i])
			{
				current_quote = '\0';
				if (quote_removal_mode)
				{
					i++;
					continue;
				}
			}
		}
		if (content[i] == '$' && current_quote != '\'')
		{
			i++;
			if (content[i] == '\0')
			{
				expanded[j++] = '$';
				break;
			}
			if (content[i] == '?')
			{
				var_value = ft_itoa(g_mini.exit_status);
				if (var_value)
				{
					ft_strcpy(&expanded[j], var_value);
					j += ft_strlen(var_value);
					free(var_value);
				}
				i++;
				continue;
			}
			var_name = extract_var_name(content, &i);
			if (!var_name)
				return (NULL);
			var_value = handle_special_vars(env, var_name);
			free(var_name);
			if (var_value && *var_value)
			{
				ft_strcpy(&expanded[j], var_value);
				j += ft_strlen(var_value);
			}
			continue;
		}
		expanded[j++] = content[i++];
	}

	expanded[j] = '\0';
	return (expanded);
}

void	split_and_expand_variables(t_env *env, t_list **node)
{
	t_list	*current_node;
	char	*expanded_content;

	current_node = *node;
	expanded_content = remove_quotes_and_expand(env, current_node->content);
	current_node->content = expanded_content;
}

void expand_variables_in_list(t_env *env, t_list **list)
{
    t_list *current = *list;
    while (current)
    {
        char *expanded_content = remove_quotes_and_expand(env, current->content);
        free(current->content);
        current->content = expanded_content;
        current = current->next;
    }
}

void merge_fragmented_nodes(t_list **list)
{
    t_list *current = *list;
    t_list *next_node;

    while (current && current->next)
    {
        next_node = current->next;
        if (next_node->separated_by_space == 0)
        {
            char *merged_content = _malloc(strlen(current->content) + strlen(next_node->content) + 1, 'm');
            if (!merged_content)
                return;

            strcpy(merged_content, current->content);
            strcat(merged_content, next_node->content);

            // free(current->content);
            current->content = merged_content;

            current->next = next_node->next;
            if (next_node->next)
                next_node->next->prev = current;

            // free(next_node->content);
            // free(next_node);
            continue;
        }
        current = current->next;
    }
}


void	merge_export_assignment(t_list **list)
{
	t_list	*current;
	t_list	*var_node;
	t_list	*val_node;
	char	*val_content;
	size_t	val_len;
	char    *merged_content;
	size_t	len_var;
	size_t	len_val;

	current = *list;
	while (current && current->next)
	{
		if (ft_strcmp(current->content, "export") == 0 && current->next)
		{
			var_node = current->next;
			val_node = var_node->next;
			if (val_node && ft_strchr(var_node->content, '=') != NULL)
			{
				val_content = val_node->content;
				val_len = ft_strlen(val_content);
				if (val_len >= 2 && ((val_content[0] == '\''
							&& val_content[val_len - 1] == '\'')
						|| (val_content[0] == '"'
                                    && val_content[val_len- 1] == '"')))
				{
					len_var = ft_strlen(var_node->content);
					len_val = ft_strlen(val_node->content);
					merged_content = _malloc(len_var + len_val + 1, 'm');
					if (!merged_content)
						return ;
					ft_strcpy(merged_content, var_node->content);
					ft_strcat(merged_content, val_node->content);
					var_node->content = merged_content;
					var_node->next = val_node->next;
					if (val_node->next)
						val_node->next->prev = var_node;
					current = var_node;
					continue ;
				}
			}
		}
		current = current->next;
	}
}

void expand(t_env *env, t_list **list)
{
	t_list *current; 
	
    expand_variables_in_list(env, list);
    merge_export_assignment(list);
    merge_fragmented_nodes(list);
	current = *list;
	while (current)
	{
		split_and_expand_variables(env, &current);
		current = current->next;
	}
}
