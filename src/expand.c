/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:26:11 by mamir             #+#    #+#             */
/*   Updated: 2024/10/21 18:54:02 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_line(char *line,int start, bool open_close)
{
    
    if (line[start]== '\'' )
        open_close = true;
}

char *catch_expand(t_env *env, char *line)
{
    char **result;
    int i;
    bool open_close = true;
    i = 0;
    while(line[i])
    {
        if (line[i] == '$')
            parse_line(line, i+1, open_close);
        
    }
    
}

char **expand_var(t_env *env,char *line)
{
    char **result;

    result = catch_expand(env, line);
    return result;
}
