/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:49:46 by mamir             #+#    #+#             */
/*   Updated: 2024/11/05 22:04:52 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *find_env_var(t_env *env, const char *name)
{
    while (env)
    {
        if (strcmp(env->key, name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}
void update_env_var(t_env **env, const char *name, const char *value)
{
    t_env *var = find_env_var(*env, name);
    if (var)
    {
        free(var->value);
        var->value = strdup(value);
    }
    else
    {
        // Add new variable if not found
        t_env *new_var = malloc(sizeof(t_env));
        new_var->key = strdup(name);
        new_var->value = strdup(value);
        new_var->next = *env;
        *env = new_var;
    }
}

void cd(t_env **env, char **args)
{
    t_env *home_env = find_env_var(*env, "HOME");
    t_env *oldpwd_env = find_env_var(*env, "OLDPWD");
    t_env *pwd_env = find_env_var(*env, "PWD");
    char *home;
    char cwd[1024];

    // Set the home variable based on whether "HOME" is found
    if (home_env != NULL)
        home = home_env->value;
    else
        home = NULL;

    if (args[1] == NULL)
    {
        if (home == NULL)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
        if (chdir(home) != 0)
            perror("cd");
    }
    else if (strcmp(args[1], "-") == 0)
    {
        if (oldpwd_env != NULL && oldpwd_env->value != NULL)
        {
            if (chdir(oldpwd_env->value) == 0)
                printf("%s\n", oldpwd_env->value);
            else
                perror("cd");
        }
        else
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
            perror("cd");
    }

    // Update PWD and OLDPWD environment variables
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (pwd_env != NULL)
            update_env_var(env, "OLDPWD", pwd_env->value);
        update_env_var(env, "PWD", cwd);
    }
    else
    {
        perror("cd: getcwd");
    }
}


void pwd(t_env **env)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        update_env_var(env, "PWD", cwd);
    }
    else
    {
        perror("pwd: getcwd() error");
    }
}
