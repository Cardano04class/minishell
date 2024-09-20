/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:49:46 by mamir             #+#    #+#             */
/*   Updated: 2024/09/20 03:32:20 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(char **args, t_list *lst)
{
    char *home;
    char *old_pwd;
    int err = 0;
    if (!lst)
        return 1;
    home = getenv("HOME");
    old_pwd = getenv("PWD");
    
    if (strncmp("cd", args[0], 3) == 0)
    {
        if (args[1] == NULL)
        {
            err = chdir("HOME");
            if (err == -1)
                return 1;    
        }
        else if (strncmp("-", args[1], 2) == 0)
        {
            chdir(old_pwd);
            printf("%s\n", old_pwd);
        }
        
    }
    printf("hooomeee----   %s\n", home);
    return 0;
}
