/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:49:46 by mamir             #+#    #+#             */
/*   Updated: 2024/09/24 18:13:44 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char **args) 
{
    char *home = getenv("HOME");


    if (args[1] == NULL) 
    {
        if (chdir(home) != 0)
            perror("cd");
    } 
    else if (strcmp(args[1], "-") == 0) 
    {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd) 
        {
            if (chdir(oldpwd) == 0)
                printf("%s\n", oldpwd);
            else
                perror("cd");
        } 
        else 
        {
            fprintf(stderr, "OLDPWD not set\n");
        }
    }
    else 
    {
        if (chdir(args[1]) != 0)
            perror("cd");
    }
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    } 
    else 
    {
        perror("getcwd");
    }
}

void print_working_directory() 
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("getcwd() error");
    }
}
