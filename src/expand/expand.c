/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:02:51 by mamir             #+#    #+#             */
/*   Updated: 2024/12/10 14:59:09 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*expand_variable(t_env *env, const char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (strcmp(current->key, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*remove_quotes_and_expand(t_env *env, char *content)
{
	char	expanded_content[1024] = {0};
	int		i = 0, j;
	int		in_single_quote;
	int		in_double_quote;
	char var_name[256] = {0};
	int		name_idx;
	char	*var_value;
	int		k;

	i = 0, j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (content[i])
	{
		if (content[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
			continue ;
		}
		if (content[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
			continue ;
		}
		if (content[i] == '$' && !in_single_quote)
		{
			i++;
			if (content[i] == '\0')
			{
				expanded_content[j++] = '$';
				continue ;
			}
			name_idx = 0;
			while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
			{
				var_name[name_idx++] = content[i++];
			}
			var_name[name_idx] = '\0';
			var_value = expand_variable(env, var_name);
			if (var_value)
			{
				k = 0;
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
	return (strdup(expanded_content));
}

void	split_and_expand_variables(t_env *env, t_list **node)
{
	t_list	*current_node;
	char	*expanded_content;

	current_node = *node;
	expanded_content = remove_quotes_and_expand(env, current_node->content);
	current_node->content = expanded_content;
}

void	merge_adjacent_quoted_nodes(t_list **list)
{
	t_list	*current;
	char	*current_content;
	char	*next_content;
	size_t	current_len;
	size_t	next_len;
	int		should_merge;
	char	*merged_content;
	t_list	*to_delete;

	current = *list;
	while (current && current->next)
	{
		current_content = current->content;
		next_content = current->next->content;
		current_len = ft_strlen(current_content);
		next_len = ft_strlen(next_content);
		should_merge = (current_len > 0 && next_len > 0
				&& ((current_content[0] == '"' && next_content[0] == '"')
					|| (current_content[0] == '\''
						&& next_content[0] == '\'')));
		if (should_merge)
		{
			merged_content = _malloc(current_len + next_len + 1, 'm');
			if (!merged_content)
				return ;
			ft_strcpy(merged_content, current_content);
			ft_strcat(merged_content, next_content + 1);
			current->content = merged_content;
			to_delete = current->next;
			current->next = to_delete->next;
			if (to_delete->next)
				to_delete->next->prev = current;
			free(to_delete);
			continue ;
		}
		current = current->next;
	}
}

void	handle_special_variable_cases(t_env *env, t_list **list)
{
	t_list	*current;
	char	*expanded;
	char	*merged_content;
	t_list	*to_delete;

	current = *list;
	while (current)
	{
		if (current->next && (strncmp(current->content, "$", 1) == 0
				|| strncmp(current->content, "\"$", 2) == 0)
				&& current->next->content[0] != '$')
		{
			expanded = remove_quotes_and_expand(env, current->content);
			current->content = expanded;
			merged_content = _malloc(ft_strlen(current->content)
					+ ft_strlen(current->next->content) + 1, 'm');
			ft_strcpy(merged_content, current->content);
			ft_strcat(merged_content, current->next->content);
			current->content = merged_content;
			to_delete = current->next;
			current->next = to_delete->next;
			if (to_delete->next)
				to_delete->next->prev = current;
			continue ;
		}
		current = current->next;
	}
}

void	merge_fragmented_nodes(t_list **list)
{
	t_list	*current;
	char	*content;
	int		is_quote_node;
	char	*first_part;
	char	*last_part;
	char	*merged_content;
	t_list	*to_delete1;
	t_list	*to_delete2;

	current = *list;
	while (current)
	{
		content = current->content;
		is_quote_node = (content[0] == '"' || content[0] == '\'');
		if (is_quote_node && current->next && strcmp(current->next->content,
				"is") == 0 && current->next->next
			&& current->next->next->content[0] == '"')
		{
			first_part = remove_quotes_and_expand(NULL, current->content);
			last_part = remove_quotes_and_expand(NULL,
					current->next->next->content);
			merged_content = _malloc(ft_strlen(first_part)
					+ ft_strlen(current->next->content) + ft_strlen(last_part)
					+ 1, 'm');
			ft_strcpy(merged_content, first_part);
			ft_strcat(merged_content, current->next->content);
			ft_strcat(merged_content, last_part);
			current->content = merged_content;
			to_delete1 = current->next;
			to_delete2 = current->next->next;
			current->next = to_delete2->next;
			if (to_delete2->next)
				to_delete2->next->prev = current;
			free(to_delete1);
			free(to_delete2);
			continue ;
		}
		current = current->next;
	}
}

void	expand(t_env *env, t_list **list)
{
	t_list	*current;

	merge_export_assignment(list);
	merge_fragmented_nodes(list);
	current = *list;
	while (current)
	{
		split_and_expand_variables(env, &current);
		current = current->next;
	}
}
