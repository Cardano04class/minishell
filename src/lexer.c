/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:08:55 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 12:23:45 by mamir            ###   ########.fr       */
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
	int		i;
	int		j;
	t_list	*lst;
	char	*string;

	j = 0;
	j = 0;
	lst = NULL;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '|')
			ft_lstaddback(&lst, ft_lstnew("|", PIPE));
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			ft_lstaddback(&lst, ft_lstnew(">>", APPEND));
			i++;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			ft_lstaddback(&lst, ft_lstnew("<<", HEREDOC));
			i++;
		}
		else if (str[i] == '>')
			ft_lstaddback(&lst, ft_lstnew(">", INRED));
		else if (str[i] == '<')
			ft_lstaddback(&lst, ft_lstnew("<", OUTRED));
		else
		{
			string = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
			if (!string)
				return ;
			j = 0;
			if (str[i] == 34)
			{
				i++;
				while (str[i] != 34 && str[i] != '\0')
					string[j++] = str[i++];
				i++;
			}
			else if (str[i] == 39)
			{
				i++;
				while (str[i] != 39 && str[i] != '\0')
					string[j++] = str[i++];
				i++;
			}
			else
			{
				while (str[i] && !ft_isspace(str[i]) && str[i] != '|'
					&& str[i] != '>' && str[i] != '<')
					string[j++] = str[i++];
			}
			string[j] = '\0';
			ft_lstaddback(&lst, ft_lstnew(ft_strdup(string), WORD));
			free(string);
		}
		i++;
	}
	ft_lstdisplay(lst);
}

