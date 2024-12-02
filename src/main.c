#include "minishell.h"

t_global g_mini;

int empty_prompt(char *rl)
{
	int i;

	i = 0;
	while (rl[i] && (rl[i] != ' ' && rl[i] != '\t'))
	{
		i++;
	}
	return i;
}

void	prompt(char **env)
{
	char	*rl;
	t_list	*list;
	t_env *env_list;
	
	env_list = NULL;
	list = NULL;
	ft_env(env, &env_list);
	while (1)
	{
		g_mini.sig_flag = 0;
		g_mini.command = malloc(sizeof(t_cmd));
		g_mini.command->cmd = NULL;
		g_mini.command->files = NULL;
		g_mini.command->next = NULL;
		
		signal_handler(IN_PROMPT);
		rl = readline("minishell$ ");
		if (rl == NULL || !ft_strncmp(rl,"exit",5))
		{
			printf("exit\n");
			exit(0);
		}
		g_mini.sig_flag = 1;
		if (empty_prompt(rl) == 0)
		{
			free(rl);
			continue;
		}
		lexer(rl, &list);
		syntax_error(list);
		//ft_lstdisplay(list);
		parser(list);
		//TODO: expand(env_list); // SEGV in the expand(should be fixed piw) :p.
			run_heredoc(g_mini.command);
		//TODO: if (!run_builtins(&env_list)) // also a SEGV here, but i still nedd to check if it from the heredoc.
		run_cmd(g_mini.command, env_list);
		signal_handler(IN_PARENT);
		ft_lstclear(&list);
		add_history(rl);
		free(rl);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac == 1)
		prompt(env);
	else
		return (1);
	return (0);
}
