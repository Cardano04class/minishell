/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:29:48 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 14:35:30 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return ("");
}

void	split_and_expand_variables(t_env *env, t_list **node)
{
	t_list	*current_node;
	char	*expanded_content;

	current_node = *node;
	expanded_content = remove_quotes_and_expand(env, current_node->content);
	current_node->content = expanded_content;
}

void	expand_variables_in_list(t_env *env, t_list **list)
{
	t_list	*current;
	char	*expanded_content;

	current = *list;
	while (current)
	{
		if (current->content)
		{
			expanded_content = remove_quotes_and_expand(env, current->content);
			if (expanded_content[0] == '\0')
				(*list)->non_var = current->content;
			current->content = expanded_content;
		}
		current = current->next;
	}
}

void	merge_fragmented_nodes(t_list **list)
{
	t_list	*current;
	t_list	*next_node;
	char	*merged_content;

	current = *list;
	while (current && current->next)
	{
		next_node = current->next;
		if (next_node->separated_by_space == 0 && next_node->type == WORD
			&& current->type == WORD)
		{
			merged_content = _malloc(strlen(current->content)
					+ ft_strlen(next_node->content) + 1, 'm');
			ft_strcpy(merged_content, current->content);
			ft_strcat(merged_content, next_node->content);
			current->content = merged_content;
			current->next = next_node->next;
			if (next_node->next)
				next_node->next->prev = current;
			continue ;
		}
		current = current->next;
	}
}

void	expand(t_env *env, t_list **list)
{
	t_list	*current;

	current = *list;
	merge_export_assignment(list);
	expand_variables_in_list(env, list);
	merge_fragmented_nodes(list);
	while (current->next)
	{
		split_and_expand_variables(env, &current);
		current = current->next;
	}
}
