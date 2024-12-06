/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:32 by mamir             #+#    #+#             */
/*   Updated: 2024/12/06 17:31:25 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_builtins(t_env **env, t_cmd *command)
{
    if (strcmp("echo", command->cmd[0]) == 0)
        echo(command->cmd);
    else if (strcmp("export", command->cmd[0]) == 0)
        export(env, command->cmd);
    else if (strcmp("exit", command->cmd[0]) == 0)
        exit_shell(g_mini.command);
    else if (strcmp("cd", command->cmd[0]) == 0)
        cd(env, command->cmd);
    else if (strcmp("pwd", command->cmd[0]) == 0)
        pwd(env);
    else if (strcmp("env", command->cmd[0]) == 0)
        print_env(*env);
    else if (strcmp("unset",command->cmd[0]) == 0)
        unset(command->cmd, env);
    return 1;
}
