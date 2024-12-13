/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:07:23 by mamir             #+#    #+#             */
/*   Updated: 2024/12/13 17:06:01 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


#include "minishell.h"

void exit_with_status(int status)
{
    // Ensure status is between 0 and 255
    exit(status & 255);
}

int is_valid_numeric_argument(const char *arg)
{
    int i = 0;
    int sign = 0;
    int digit_found = 0;

    // Skip leading whitespace
    while (ft_isspace(arg[i]))
        i++;

    // Check for optional sign
    if (arg[i] == '+' || arg[i] == '-') {
        sign = (arg[i] == '-') ? -1 : 1;
        i++;
    }

    // Check for at least one digit
    while (ft_isdigit(arg[i])) {
        digit_found = 1;
        i++;
    }

    // Skip trailing whitespace
    while (ft_isspace(arg[i]))
        i++;

    // Valid if all characters processed and at least one digit found
    return (arg[i] == '\0' && digit_found);
}

long long parse_exit_argument(const char *arg)
{
    long long result = 0;
    int i = 0;
    int sign = 1;

    // Skip leading whitespace
    while (ft_isspace(arg[i]))
        i++;

    // Handle sign
    if (arg[i] == '-' || arg[i] == '+') {
        sign = (arg[i] == '-') ? -1 : 1;
        i++;
    }

    // Parse numeric value
    while (ft_isdigit(arg[i])) {
        result = result * 10 + (arg[i] - '0');
        
        // Check for overflow
        if (result > LLONG_MAX) {
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", arg);
            exit(2);
        }
        i++;
    }

    return result * sign;
}

void ft_exit(t_cmd *data)
{
    static int is_first_command = 1;
    int i = 0;
    int exit_status = 0;

    while (data->cmd[i]) {
        if (ft_strcmp(data->cmd[i], "exit") == 0) {
            // No arguments
            if (data->cmd[i + 1] == NULL) {
                if (is_first_command) {
                    ft_putstr_fd("exit\n", STDERR_FILENO);
                    exit_with_status(g_mini.exit_status);
                }
                return;
            }
            if (!is_valid_numeric_argument(data->cmd[i + 1])) {
                if (is_first_command) {
                    fprintf(stderr, "minishell: exit: %s: numeric argument required\n", 
                            data->cmd[i + 1]);
                    exit(2);
                }
                return;
            }
            if (data->cmd[i + 2] != NULL) {
                if (is_first_command) {
                    ft_putstr_fd("exit\n", STDERR_FILENO);
                    ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
                    g_mini.exit_status = 1;
                }
                return;
            }

            // Parse exit status
            exit_status = parse_exit_argument(data->cmd[i + 1]) & 255;
            
            // For first command, actually exit
            if (is_first_command) {
                ft_putstr_fd("exit\n", STDERR_FILENO);
                exit_with_status(exit_status);
            }
        }
        i++;
        is_first_command = 0;
    }
}
// void exiter(int number)
// {
//     exit(number);
// }

// void    pars_str(size_t *r, char *arg, int *i, int sign)
// {
//     while (ft_isdigit(arg[*i]))
//     {
//         *r = *r * 10 + (arg[*i] - '0');
//         if ((*r > 9223372036854775807 && sign == 1)
//             || (*r > 9223372036854775808UL && sign == -1))
//         {
//             printf("minishell: exit:  \"%s\" : numeric argument required\n", arg);
//             exiter(2);
//         }
//         (*i)++;
//     }
// }

// void    pars_exit_arg(char *arg)
// {
//     size_t  r;
//     int     i;
//     int     sign;

//     r = 0;
//     i = 0;
//     sign = 1;
//     while (ft_isspace(arg[i]))
//         i++;
//     if (arg[i] == '-' || arg[i] == '+')
//     {
//         if (arg[i++] == '-')
//             sign = -1;
//     }
//     pars_str(&r, arg, &i, sign);
//     while (ft_isspace(arg[i]))
//         i++;
//     if (arg[i] != '\0')
//     {
//         printf("minishell: exit:  \"%s\" : numeric argument required\n", arg);
//         exiter(2);
//     }
//     exiter(((long)r * sign) & 255);
// }


// void    ft_exit(t_cmd *data)
// {
//     int i;
//     int is_first_command;

//     i = 0;
//     is_first_command = 1;
//     while (data->cmd[i])
//     {
//         if (ft_strcmp(data->cmd[i], "exit") == 0)
//         {
//             if (data->cmd[i + 1] == NULL)
//             {
//                 if (is_first_command)
//                     ft_putstr_fd("exit\n", 2);
//                 exiter(g_mini.exit_status);
//             }
//             else if (data->cmd[i + 2] != NULL)
//             {
//                 if (is_first_command)
//                     ft_putstr_fd("exit\n", 2);
//                 ft_putstr_fd("minishell: exit: too many arguments\n", 2);
//                 if (!is_first_command)
//                     g_mini.exit_status = 1;
//             }
//             else
//                 pars_exit_arg(data->cmd[i + 1]);
//         }
//         i++;
//         is_first_command = 0;
//     }
// }