/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:08:55 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/04 16:18:24 by mamir            ###   ########.fr       */
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

void	lexer(char **av)
{
	int i;
	int j;
	int k;
	t_list *lst;
	char *str;

	j = 0;
	lst = NULL;
	while (av[j] != NULL)
	{
		i = 0;
		while (av[j][i] != '\0')
		{
			if (ft_isspace(av[j][i]))
			{
				i++;
			}
			else if (av[j][i] == '|')
			{
				ft_lstaddback(&lst, ft_lstnew("|", PIPE));
			}
			else if (av[j][i] == '>' && av[j][i + 1] == '>')
			{
				ft_lstaddback(&lst, ft_lstnew(">>", APPEND));
				i++;
			}
			else if (av[j][i] == '<' && av[j][i + 1] == '<')
			{
				ft_lstaddback(&lst, ft_lstnew("<<", HEREDOC));
				i++;
			}
			else if (av[j][i] == '>')
			{
				ft_lstaddback(&lst, ft_lstnew(">", INRED));
			}
			else if (av[j][i] == '<')
			{
				ft_lstaddback(&lst, ft_lstnew("<", OUTRED));
			}
			else
			{
				k = 0;
				str = ft_strdup(av[j]);
				ft_lstaddback(&lst, ft_lstnew(str, CMD));
				break ;
			}
			i++;
		}
		j++;
	}
	ft_lstdisplay(lst);
}
