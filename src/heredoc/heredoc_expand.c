/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:28:35 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/18 18:06:27 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_in_heredoc(char *content)
{
	int		expanded_len;
	char	*expanded_content;

	expanded_len = calculate_var_expansion_length(content);
	expanded_content = copy_expanded_content(content, expanded_len);
	return (expanded_content);
}
