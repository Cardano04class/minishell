/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:30:33 by mamir             #+#    #+#             */
/*   Updated: 2024/09/13 20:31:02 by mamir            ###   ########.fr       */
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
    int single_counter = 0;
    int double_counter = 0;
    while (str[i])
    {
        if (str[i] == '"')
            double_counter++;
        if (str[i] == '\'')
            single_counter++;
        i++;
    }
    if (double_counter % 2 == 0 && single_counter % 2 == 0)
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
                return(ft_putstr_fd("syntax error: command not found\n", 1));  
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
