/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:28:54 by mamir             #+#    #+#             */
/*   Updated: 2024/11/03 15:21:40 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_special_char(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

static char *create_token(char *str, int start, int end)
{
    return ft_substr(str, start, end - start);
}

void lexer(char *str, t_list **lst)
{
    int i;
    int start;
    t_state state;
    char quote_char;

    i = 0;
    start = 0;
    state = INITIAL;
    while (str[i] != '\0')
    {
        if (state == INITIAL)
        {
            if (ft_isspace(str[i]))
                state = IN_WHITESPACE;
            else if (is_special_char(str[i]))
                state = IN_SPECIAL;
            else if (str[i] == 34 || str[i] == 39)
            {
                quote_char = str[i];
                state = IN_QUOTE;
                start = i;
            }
            else
            {
                state = IN_WORD;
                start = i;
            }
        }
        if (state == IN_WHITESPACE)
        {
            while (ft_isspace(str[i]))
                i++;
            state = INITIAL;
            --i;
        }
        else if (state == IN_SPECIAL)
        {
            if (str[i] == '|')
			    ft_lstaddback(lst, ft_lstnew(ft_strdup("|"), PIPE));
            else if (str[i] == '>' && str[i + 1] == '>')
            {
                ft_lstaddback(lst, ft_lstnew(ft_strdup(">>"), APPEND));
                i++;
            }
            else if (str[i] == '<' && str[i + 1] == '<')
            {
                ft_lstaddback(lst, ft_lstnew(ft_strdup("<<"), HEREDOC));
                i++;
            }
            else if (str[i] == '>')
			    ft_lstaddback(lst, ft_lstnew(ft_strdup(">"), INRED));
            else if (str[i] == '<')
			    ft_lstaddback(lst, ft_lstnew(ft_strdup("<"), OUTRED));
            state = INITIAL;
        }
        else if (state == IN_WORD || state == IN_QUOTE)
        {
            if (state == IN_WORD)
            {
                while (str[i] != '\0' && !is_special_char(str[i]) && !ft_isspace(str[i]) && str[i] != 34 && str[i] != 39)
                    i++;
                ft_lstaddback(lst, ft_lstnew(create_token(str, start, i), WORD));
                // printf("index : %d | str[i] = %s\n", i, &str[i]);
                if (str[i] == 34 || str[i] == 39)
                {
                    quote_char = str[i];
                    state = IN_QUOTE;
                    start = i;
                    continue ;
                }
                else if (is_special_char(str[i]))
                {
                    state = IN_SPECIAL;
                    continue ;
                }
                state = INITIAL;
                --i;
            }
            else if (state == IN_QUOTE)
            {
                i++;
                while (str[i] != '\0' && str[i] != quote_char)
                    i++;
                if (str[i] == quote_char)
                    i++;
                ft_lstaddback(lst, ft_lstnew(create_token(str, start, i), WORD));
                if (is_special_char(str[i]))
                {
                    state = IN_SPECIAL;
                    continue ;
                }
                state = INITIAL;
                --i;
            }
        }
        i++;
    }
}