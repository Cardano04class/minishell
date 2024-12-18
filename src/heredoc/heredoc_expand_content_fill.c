/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_content_fill.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:38 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:07:13 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
