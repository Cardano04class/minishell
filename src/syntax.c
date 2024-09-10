/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:30:33 by mamir             #+#    #+#             */
/*   Updated: 2024/09/10 15:10:42 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(t_list *token)
{
	if (token->type == PIPE || token->type == INRED || token->type == OUTRED
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	return (0);
}

void	invalid_position(t_list *list)
{
	if (is_special(list))
	{
		printf("syntax error: '%s'\n", list->content);
	}
	else if (list->next == NULL || list->prev == NULL)
	{
		printf("syntax error: '%s'\n", list->content);
	}
}

int quotes_closed(char *str)
{
    int i = 0;
    char quote;
    if (str[i] == 34 || str[i] == 39)
        quote = str[i];
    i++;
    while (str[i])
    {
        if (str[i] == quote)
            return 1;
        i++;
    }
    return 0;
}

void syntax_error(t_list *list)
{
    while (list)
    {   
        if (list->type == WORD)
        {
            if (list->content[0] == 34 || list->content[0] == 39)
            {
                if(!quotes_closed(list->content))
                    return(ft_putstr_fd("syntax error: command not found\n", 1));  
            }    
        }
        if (is_special(list))
        {
            if (list->next == NULL || (list->prev == NULL && list->type == PIPE))
            {
                printf("syntax error: '%s'\n", list->content);
                break ;
            }
            if (list->next && is_special(list->next))
            {
                printf("syntax error: consecutive special symbols\n");
                return;    
            }
        }
        list = list->next;
    }
}