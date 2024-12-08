/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:30:33 by mamir             #+#    #+#             */
/*   Updated: 2024/12/08 22:31:53 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_special(t_list *token)
{
    if (!token)
        return (0); // Ensure token is valid
    return (token->type == PIPE || token->type == INRED
            || token->type == OUTRED || token->type == APPEND
            || token->type == HEREDOC);
}

t_error create_error(t_error_type type, char *token)
{
    t_error error;

    error.type = type;
    if (token)
        error.token = ft_strdup(token);
    else
        error.token = NULL;
    return error;
}

t_error check_quotes(char *str)
{
    int i = 0;
    int single_quote = 0;
    int double_quote = 0;

    if (!str)
        return create_error(NO_ERROR, NULL);
    while (str[i])
    {
        if (str[i] == '\'' && !double_quote)
            single_quote = !single_quote;
        else if (str[i] == '"' && !single_quote)
            double_quote = !double_quote;
        i++;
    }
    if (single_quote || double_quote)
        return create_error(UNCLOSED_QUOTES, str);
    return create_error(NO_ERROR, NULL);
}

t_error check_special_token_position(t_list *token)
{
    if (!token)
        return create_error(NO_ERROR, NULL);
    if (!token->next && is_special(token))
        return create_error(MISSING_CONTEXT, token->content);
    if (!token->prev && token->type == PIPE)
        return create_error(PIPE_AT_START, token->content);
    if (token->next && is_special(token) && is_special(token->next))
        return create_error(CONSECUTIVE_SPECIAL, token->content);
    return create_error(NO_ERROR, NULL);
}

t_error syntax_check(t_list *list)
{
    t_error error;

    error.type = NO_ERROR;
    error.token = NULL;
    while (list)
    {
        if (list->type == WORD)
        {
            error = check_quotes(list->content);
            if (error.type != NO_ERROR)
                return error;
        }
        if (is_special(list))
        {
            error = check_special_token_position(list);
            if (error.type != NO_ERROR)
                return error;
        }
        list = list->next;
    }
    return create_error(NO_ERROR, NULL);
}

int syntax_error(t_list *list)
{
    t_error error;

    error = syntax_check(list);
    if (error.type != NO_ERROR)
    {
        print_error(error);
        return 1;
    }
    return 0;
}

void print_error(t_error error)
{
    if (error.type == UNCLOSED_QUOTES)
        ft_putstr_fd("syntax error: unclosed quotes\n", 2);
    else if (error.type == INVALID_POSITION || error.type == PIPE_AT_START
             || error.type == MISSING_CONTEXT)
    {
        ft_putstr_fd("syntax error: '", 2);
        if (error.token)
            ft_putstr_fd(error.token, 2);
        else
            ft_putstr_fd("(null)", 2);
        ft_putstr_fd("'\n", 2);
    }
    else if (error.type == CONSECUTIVE_SPECIAL)
        ft_putstr_fd("syntax error: consecutive special symbols\n", 2);
    else
        ft_putstr_fd("syntax error: unknown error\n", 2);
}
