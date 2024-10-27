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
	g_mini.command = malloc(sizeof(t_cmd));
	g_mini.command->files = NULL;
	g_mini.command->heredoc = NULL;
	g_mini.command->next = NULL;
	ft_env(env, &env_list);
	while (1)
	{
		rl = readline("Mini_segfault$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (empty_prompt(rl) == 0)
		{
			free(rl);
			continue;
		}
		lexer(rl, &list);
		syntax_error(list);
		parser(list);
		expand(env_list);
		run_builtins(&env_list);
		ft_lstclear(&list);
		add_history(rl);
		free(rl);
	}
	clear_history();
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
