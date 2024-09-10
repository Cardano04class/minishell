/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:46:08 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/10 14:46:10 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(char **content)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->content = content;
	new->input_fd = 0;
	new->output_fd = 1;
	new->next = NULL;
	return (new);
}