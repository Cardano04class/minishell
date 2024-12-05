/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/05 18:33:59 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_builtins(t_env **env)
{
    t_cmd *tmp = g_mini.command;

    if (strcmp("echo", tmp->cmd[0]) == 0)
        echo(tmp->cmd);
    else if (strcmp("export", tmp->cmd[0]) == 0)
        export(env, tmp->cmd);
    else if (strcmp("exit", tmp->cmd[0]) == 0)
        exit_shell(tmp);
    else if (strcmp("cd", tmp->cmd[0]) == 0)
        cd(env, tmp->cmd);
    else if (strcmp("pwd", tmp->cmd[0]) == 0)
        pwd(env);
    else if (strcmp("env", tmp->cmd[0]) == 0)
        print_env(*env);
    else if (strcmp("unset",tmp->cmd[0]) == 0)
        unset(tmp->cmd, env);
    else
        run_cmd(g_mini.command, &env);
}
