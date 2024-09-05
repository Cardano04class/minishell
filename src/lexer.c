/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:08:55 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 09:09:15 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == 32)
		return (1);
	return (0);
}

void	lexer(char *str)
{
	int j;
	int k;
	t_list *lst;
	char *string;

	j = 0;
	lst = NULL;
	
		while (str[j] != '\0')
		{
			if (ft_isspace(str[j]))
				j++;
			else if (str[j] == '|')
				ft_lstaddback(&lst, ft_lstnew("|", PIPE));
			else if (str[j] == '>' && str[j+1] == '>')
			{
				ft_lstaddback(&lst, ft_lstnew(">>", APPEND));
				j++;
			}
			else if (str[j] == '<' && str[j+1] == '<')
			{
				ft_lstaddback(&lst, ft_lstnew("<<", HEREDOC));
				j++;
			}
			else if (str[j] == '>')
				ft_lstaddback(&lst, ft_lstnew(">", INRED));
			else if (str[j] == '<')
				ft_lstaddback(&lst, ft_lstnew("<", OUTRED));
			else
			{
				k = 0;
				string = ft_strdup(&str[j]);
				ft_lstaddback(&lst, ft_lstnew(str, CMD));
				break ;
			}
			j++;
		}
	ft_lstdisplay(lst);
}
