/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/08 15:57:56 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_builtins(t_env **env, t_cmd *command)
{
    if (ft_strcmp("echo", command->cmd[0]) == 0)
        echo(command->cmd);
    else if (ft_strcmp("export", command->cmd[0]) == 0)
        export(env, command->cmd);
    else if (ft_strcmp("exit", command->cmd[0]) == 0)
        exit_shell(g_mini.command);
    else if (ft_strcmp("cd", command->cmd[0]) == 0)
        cd(env, command->cmd);
    else if (ft_strcmp("pwd", command->cmd[0]) == 0)
        pwd(env);
    else if (ft_strcmp("env", command->cmd[0]) == 0)
        print_env(*env);
    else if (ft_strcmp("unset",command->cmd[0]) == 0)
        unset(command->cmd, env);
    return 1;
}
