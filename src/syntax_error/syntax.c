/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:30:33 by mamir             #+#    #+#             */
/*   Updated: 2024/09/18 17:53:46 by mamir            ###   ########.fr       */
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
    int single_quote_open = 0;
    int double_quote_open = 0;

    while (str[i])
    {
        if (str[i] == '\'') 
        {
            if (double_quote_open == 0)  
                single_quote_open = !single_quote_open;
        }
        else if (str[i] == '"')
        {
            if (single_quote_open == 0)  
                double_quote_open = !double_quote_open;
        }
        i++;
    }
    if (single_quote_open == 0 && double_quote_open == 0)
        return 1;
    else
        return 0;
}

void syntax_error(t_list *list)
{
    while (list)
    {   
        if (list->type == WORD)
        {
            if(!quotes_closed(list->content))
            {
                ft_putstr_fd("syntax error: command not found\n", 1);
                return ;  
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
