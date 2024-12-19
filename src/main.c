/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:49:16 by mamir             #+#    #+#             */
/*   Updated: 2024/12/19 17:14:26 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_mini;

int	empty_prompt(char *rl)
{
	int	i;

	i = 0;
	while (rl[i] && (rl[i] != ' ' && rl[i] != '\t'))
	{
		i++;
	}
	return (i);
}

void	prompt(char **env)
{
	char	*rl;
	t_list	*list;

	g_mini.env = NULL;
	list = NULL;
	ft_env(env, &g_mini.env);
	signal(SIGQUIT, SIG_IGN);
	g_mini.exit_status = 0;
	while (1)
	{
		g_mini.sig_flag = 0;
		g_mini.command = _malloc(sizeof(t_cmd), 'm');
		g_mini.command->cmd = NULL;
		g_mini.command->files = NULL;
		g_mini.command->next = NULL;
		signal(SIGINT, handle_sigint);
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			g_mini.exit_status = 127;
			break ;
		}
		if (empty_prompt(rl) == 0)
			continue ;
		lexer(rl, &list);
		if (!syntax_error(list))
		{
			expand(g_mini.env, &list);
			parser(list);
			run_heredoc(g_mini.command);
			if (g_mini.command->cmd[0] != NULL)
				execution(g_mini.command);
		}
		ft_lstclear(&list);
		add_history(rl);
	}
	_malloc(0, 'f');
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
	{
		prompt(env);
		return (g_mini.exit_status);
	}
	else
		return (1);
}
