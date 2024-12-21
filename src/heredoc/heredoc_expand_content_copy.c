/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_content_copy.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:41 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:07:22 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
