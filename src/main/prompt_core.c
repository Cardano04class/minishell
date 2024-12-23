/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 21:10:44 by mobouifr          #+#    #+#             */
/*   Updated: 2024/12/22 21:48:48 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_prompt(char *rl)
{
	char	*str;
	int		i;

	i = 0;
	str = remove_leading_spaces(rl);
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	intialise_prompt_variables(void)
{
	g_mini.sig_flag = 0;
	g_mini.command = _malloc(sizeof(t_cmd), 'm');
	g_mini.command->cmd = NULL;
	g_mini.command->files = NULL;
	g_mini.command->next = NULL;
}

void	parse_and_execute(t_list *list)
{
	expand(g_mini.env, &list);
	parser(list);
	run_heredoc(g_mini.command);
	if (g_mini.exit_status != 130)
		execution(g_mini.command);
}

int	rl_is_null(char *rl)
{
	if (rl == NULL)
	{
		printf("exit\n");
		g_mini.exit_status = 127;
		return (1);
	}
	return (0);
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
		intialise_prompt_variables();
		signal_handler(IN_PROMPT);
		rl = readline("minishell$ ");
		if (rl_is_null(rl))
			break ;
		if (empty_prompt(rl))
			continue ;
		lexer(rl, &list);
		if (!syntax_error(list))
			parse_and_execute(list);
		ft_lstclear(&list);
		add_history(rl);
	}
	_malloc(0, 'f');
}
