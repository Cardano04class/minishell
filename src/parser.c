/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:44:40 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/24 11:32:26 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_list *lst, t_cmd **cmd)
{
	char 	**str;
	int		i;
	int		j;
	
	j = 0;
	i = 0;
	// allocat o **cmd 
	while (lst != NULL)
	{
		if (lst->type == WORD)
		{	
			str = ft_ssplit(lst->content);
			while (str[j] != NULL)
			{
				strncpy((*cmd)->cmd[j], str[j], ft_strlen(str[j]));//string
				j++;
			}
		}
	}
}
