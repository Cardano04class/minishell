/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:07:23 by mamir             #+#    #+#             */
/*   Updated: 2024/12/14 18:32:06 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exiter(int number)
{
    exit(number);
}

void    pars_str(size_t *r, char *arg, int *i, int sign)
{
    while (ft_isdigit(arg[*i]))
    {
        *r = *r * 10 + (arg[*i] - '0');
        if ((*r > 9223372036854775807 && sign == 1)
            || (*r > 9223372036854775808UL && sign == -1))
        {
            printf("minishell: exit:  \"%s\" : numeric argument required\n", arg);
            exiter(2);
        }
        (*i)++;
    }
}

void    pars_exit_arg(char *arg)
{
    size_t  r;
    int     i;
    int     sign;

    r = 0;
    i = 0;
    sign = 1;
    while (ft_isspace(arg[i]))
        i++;
    if (arg[i] == '-' || arg[i] == '+')
    {
        if (arg[i++] == '-')
            sign = -1;
    }
    pars_str(&r, arg, &i, sign);
    while (ft_isspace(arg[i]))
        i++;
    if (arg[i] != '\0')
    {
        printf("minishell: exit:  \"%s\" : numeric argument required\n", arg);
        exiter(2);
    }
    exiter(((long)r * sign) & 255);
}

void    ft_exit(t_cmd *data)
{
    int i;

    i = 0;
    while (data)
    {       
        while (data->cmd[i])
        {
            if (ft_strcmp(data->cmd[i], "exit") == 0)
            {
                if (g_mini.exit_flag == 0) 
                {
                    ft_putstr_fd("exit\n", STDOUT_FILENO);
                    g_mini.exit_flag = 1;
                }
                if (data->cmd[i + 1] == NULL)
                {
                    exiter(g_mini.exit_status);
                }
                else if (data->cmd[i + 2] != NULL)
                {
                    ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
                    g_mini.exit_status = 1;
                }
                else
                {
                    pars_exit_arg(data->cmd[i + 1]);
                }
            }
            i++;
        }
        data = data->next;
    }
}
