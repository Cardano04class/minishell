/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:28:54 by mamir             #+#    #+#             */
/*   Updated: 2024/09/05 12:28:55 by mamir            ###   ########.fr       */
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
	int token_length;

	j = 0;
	i = 0;
	lst = NULL;
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
			token_length = 0;
			if (str[i] == 34)  
			{
				i++;  
				while (str[i + token_length] != 34 && str[i + token_length] != '\0') 
					token_length++;
			}	
			else if (str[i] == 39) 
			{
				i++;  
				while (str[i + token_length] != 39 && str[i + token_length] != '\0')
					token_length++;				
			}
			else
			{
				while (str[i + token_length] && !ft_isspace(str[i + token_length]) && 
					str[i + token_length] != '|' && str[i + token_length] != '>' && 
					str[i + token_length] != '<')
				{
					token_length++;
				}
			}
			string = malloc(sizeof(char) * (token_length + 1));
			if (!string)
				return;
			j = 0;
			while (j < token_length)
			{
				string[j] = str[i];
				i++;
				j++;
			}
			string[j] = '\0';
			if (string[0] != '\0')
				ft_lstaddback(&lst, ft_lstnew(ft_strdup(string), WORD));  
			free(string);
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	ft_lstdisplay(lst);
}