/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:12:47 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/22 21:50:57 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	if (g_mini.sig_flag == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
	g_mini.exit_status = 130;
}

void	handle_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "Quit (core dumped)\n", 19);
	g_mini.exit_status = 131;
}

void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	_malloc(0, 'f');
	g_mini.exit_status = 130;
	exit(130);
}

void	signal_handler(int sig)
{
	if (sig == IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, handle_sigquit);
	}
	else if (sig == IN_PROMPT)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == IN_HEREDOC)
	{
		signal(SIGINT, heredoc_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
