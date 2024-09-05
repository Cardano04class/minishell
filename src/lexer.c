/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:08:55 by mobouifr          #+#    #+#             */
/*   Updated: 2024/09/05 10:25:40 by mamir            ###   ########.fr       */
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

static int	copy_token(char *str, char **string)
{
	int i = 0;
	int j = 0;
	
	*string = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(*string))
		return (0);
	if (str[i] == 34) // Double quote
	{
		i++;
		while (str[i] != 34 && str[i] != '\0')
			(*string)[j++] = str[i++];
		i++;
	}
	else if (str[i] == 39) // Single quote
	{
		i++;
		while (str[i] != 39 && str[i] != '\0')
			(*string)[j++] = str[i++];
		i++;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]) && str[i] != '|'
			&& str[i] != '>' && str[i] != '<')
			(*string)[j++] = str[i++];
	}
	(*string)[j] = '\0';
	return i; // Return how many characters were copied
}

void	lexer(char *str)
{
	int		i;
	t_list	*lst;
	char	*string;

	i = 0;
	lst = NULL;
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
			i += copy_token(&str[i], &string); // Call the new function
			ft_lstaddback(&lst, ft_lstnew(ft_strdup(string), WORD));
			free(string);
		}
		i++;
	}
	ft_lstdisplay(lst);
}

