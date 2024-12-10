/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:43:24 by mamir             #+#    #+#             */
/*   Updated: 2024/12/10 22:53:03 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void expand_variables_in_list(t_env *env, t_list **list)
{
    t_list *current;
    char *expanded_content;

    current = *list;
    while (current)
    {
        printf("Expanding Node: %s\n", current->content);
        // Use expand_variable with correct arguments
        expanded_content = expand_variable(env, current->content);
        if (expanded_content)
        {
            free(current->content);
            current->content = expanded_content;
        }
        current = current->next;
    }
}


void merge_fragmented_nodes(t_list **list)
{
    t_list *current;
    t_list *next_node;

    current = *list;
    while (current && current->next)
    {
        next_node = current->next;
        // Merge nodes only if they are not separated by a space
        if (next_node->separated_by_space == 0)
        {
            char *merged_content = _malloc(strlen(current->content) + strlen(next_node->content) + 1, 'm');
            ft_strcpy(merged_content, current->content);
            ft_strcat(merged_content, next_node->content);

            free(current->content);
            current->content = merged_content;

            current->next = next_node->next;
            if (next_node->next)
                next_node->next->prev = current;

            free(next_node->content);
            free(next_node);

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
    merge_export_assignment(list);
    expand_variables_in_list(env, list);
    merge_fragmented_nodes(list);
	t_list *current = *list;
	while (current)
	{
		split_and_expand_variables(env, &current);
		current = current->next;
	}
}
