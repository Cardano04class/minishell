/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:37:54 by mamir             #+#    #+#             */
/*   Updated: 2024/12/18 18:05:06 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted_value(char *content)
{
	size_t	len;

	if (!content)
		return (0);
	len = ft_strlen(content);
	if (len >= 2)
	{
		if ((content[0] == '\'' && content[len - 1] == '\'')
			|| (content[0] == '"' && content[len - 1] == '"'))
			return (1);
	}
	return (0);
}

char	*merge_var_and_value(t_list *var_node, t_list *val_node)
{
	size_t	len_var;
	size_t	len_val;
	char	*merged_content;

	len_var = ft_strlen(var_node->content);
	len_val = ft_strlen(val_node->content);
	merged_content = _malloc(len_var + len_val + 1, 'm');
	if (!merged_content)
		return (NULL);
	ft_strcpy(merged_content, var_node->content);
	ft_strcat(merged_content, val_node->content);
	return (merged_content);
}

void	merge_and_update_nodes(t_list *var_node, t_list *val_node)
{
	char	*merged_content;

	merged_content = merge_var_and_value(var_node, val_node);
	if (!merged_content)
		return ;
	var_node->content = merged_content;
	var_node->next = val_node->next;
	if (val_node->next)
		val_node->next->prev = var_node;
}

void	merge_export_assignment(t_list **list)
{
	t_list	*current;

	current = *list;
	while (current && current->next)
	{
		if (ft_strcmp(current->content, "export") == 0 && current->next)
		{
			if (current->next->next && ft_strchr(current->next->content, '=')
				&& is_quoted_value(current->next->next->content))
			{
				merge_and_update_nodes(current->next, current->next->next);
				current = current->next;
				continue ;
			}
		}
		current = current->next;
	}
}
