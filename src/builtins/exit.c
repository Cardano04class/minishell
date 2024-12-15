/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:07:23 by mamir             #+#    #+#             */
/*   Updated: 2024/12/15 14:59:38 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Custom function to convert string to long long with overflow handling
long long ft_atoll(const char *str)
{
    long long result = 0;
    int sign = 1;
    
    // Skip leading whitespace
    while (ft_isspace(*str))
        str++;
    
    // Handle sign
    if (*str == '-' || *str == '+')
    {
        sign = (*str == '-') ? -1 : 1;
        str++;
    }
    
    // Process digits
    while (ft_isdigit(*str))
    {
        // Check for potential overflow
        if (result > LLONG_MAX / 10 || 
            (result == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10))
        {
            // Overflow occurred
            return sign == 1 ? LLONG_MAX : LLONG_MIN;
        }
        
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return result * sign;
}

// Helper function to validate if a string is a valid numeric argument
int is_valid_numeric_arg(const char *arg)
{
    size_t i = 0;
    
    // Skip leading whitespace
    while (ft_isspace(arg[i]))
        i++;
    
    // Check for optional sign
    if (arg[i] == '-' || arg[i] == '+')
        i++;
    
    // Ensure at least one digit follows
    if (!ft_isdigit(arg[i]))
        return 0;
    
    // Check digits
    while (ft_isdigit(arg[i]))
        i++;
    
    // Skip trailing whitespace
    while (ft_isspace(arg[i]))
        i++;
    
    // Argument is valid if we've reached the end of the string
    return arg[i] == '\0';
}

// Check if current command is the last in the pipeline
int is_last_command(t_cmd *current)
{
    t_cmd *temp = current;
    while (temp)
    {
        if (temp->next == NULL)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// Modified exit function to match Bash behavior
void ft_exit(t_cmd *data)
{
    t_cmd *current = data;
    
    // Process exit command
    while (current)
    {
        // Check if current command is exit
        if (ft_strcmp(current->cmd[0], "exit") == 0)
        {
            // No arguments: exit with last exit status only if last command
            if (!current->cmd[1])
            {
                if (is_last_command(current) && g_mini.exit_pipe != 1)
                {
                    ft_putstr_fd("exit\n", 2);
                    exit(g_mini.exit_status);
                }
                return;
            }
            
            // Multiple arguments: too many arguments error
            if (current->cmd[2])
            {
                if (is_last_command(current))
                {
                    ft_putstr_fd("exit\n", 2);
                    ft_putstr_fd("minishell: exit: too many arguments\n", 2);
                    g_mini.exit_status = 1;
                    return;
                }
                return;
            }
            
            // Single argument: validate and exit
            char *arg = current->cmd[1];
            if (!is_valid_numeric_arg(arg))
            {
                if (is_last_command(current))
                {
                    ft_putstr_fd("exit\n", 2);
                    ft_putstr_fd("minishell: exit: ", 2);
                    ft_putstr_fd(arg, 2);
                    ft_putstr_fd(": numeric argument required\n", 2);
                    exit(2);
                }
                return;
            }
            
            // Convert argument to exit status (use modulo 256 for Bash-like behavior)
            long long result = ft_atoll(arg);
            g_mini.exit_status = (unsigned char)result;
            
            // Exit only if this is the last command
            if (is_last_command(current) && g_mini.exit_pipe != 1)
            {
                
                ft_putstr_fd("exit\n", 2);
                exit(g_mini.exit_status);
            }
            
            return;
        }
        
        current = current->next;
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

// void ft_exit(t_cmd *data)
// {
//     t_cmd *current = data;
//     int has_multiple_nodes = 0;

//     if (current && current->next)
//         has_multiple_nodes = 1;

//     while (current)
//     {
//         if (ft_strcmp(current->cmd[0], "exit") == 0)
//         {
//             if (current->cmd[1])
//             {
//                 char *arg = current->cmd[1];
//                 size_t i = 0;
//                 int sign = 1;
//                 while (ft_isspace(arg[i]))
//                     i++;
//                 if (arg[i] == '-' || arg[i] == '+')
//                 {
//                     if (arg[i] == '-')
//                         sign = -1;
//                     i++;
//                 }
//                 if (!ft_isdigit(arg[i]))
//                 {
//                     ft_putstr_fd("bash: exit: ", 2);
//                     ft_putstr_fd(arg, 2);
//                     ft_putstr_fd(": numeric argument required\n", 2);
//                     g_mini.exit_status = 2;
//                     if (!has_multiple_nodes)
//                     {
//                         ft_putstr_fd("exit\n", 2);
//                         exiter(2);
//                     }
//                     return;
//                 }
//                 long long result = 0;
//                 while (ft_isdigit(arg[i]))
//                 {
//                     result = result * 10 + (arg[i] - '0');
//                     if (result > 9223372036854775807LL)
//                     {
//                         ft_putstr_fd("bash: exit: ", 2);
//                         ft_putstr_fd(arg, 2);
//                         ft_putstr_fd(": numeric argument required\n", 2);
//                         g_mini.exit_status = 2;
//                         if (!has_multiple_nodes)
//                         {
//                             ft_putstr_fd("exit\n", 2);
//                             exiter(2);
//                         }
//                         return;
//                     }
//                     i++;
//                 }
//                 while (ft_isspace(arg[i]))
//                     i++;
//                 if (arg[i] != '\0')
//                 {
//                     ft_putstr_fd("bash: exit: ", 2);
//                     ft_putstr_fd(arg, 2);
//                     ft_putstr_fd(": numeric argument required\n", 2);
//                     g_mini.exit_status = 2;
//                     if (!has_multiple_nodes)
//                     {
//                         ft_putstr_fd("exit\n", 2);
//                         exiter(2);
//                     }
//                     return;
//                 }
//                 g_mini.exit_status = (int)((result * sign) & 255);

//                 // If there are more arguments after a valid numeric one
//                 if (current->cmd[2])
//                 {
//                     if (!has_multiple_nodes)
//                     {
//                         ft_putstr_fd("exit\n", 2);
//                         ft_putstr_fd("minishell: exit: too many arguments\n", 2);
//                     }
//                     g_mini.exit_status = 1;
//                     break;
//                 }
//             }
//             else if (!current->cmd[1])
//             {
//                 if (!has_multiple_nodes)
//                 {
//                     ft_putstr_fd("exit\n", 2);
//                     exiter(g_mini.exit_status);
//                 }
//             }
//         }
//         if (!current->next)
//         {
//             if (!has_multiple_nodes)
//             {
//                 ft_putstr_fd("exit\n", 2);
//                 exiter(g_mini.exit_status);
//             }
//             return;
//         }

//         current = current->next;
//     }
// }
