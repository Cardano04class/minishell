#include "minishell.h"

void	prompt(char **env)
{
	char	*rl;
	char **args;
	t_list *list;
	t_env *env_list;

	list = NULL;
	
	while (1)
	{
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		args = ft_split(rl, ' ');
		lexer(rl, &list);
		syntax_error(list);
		if (strncmp("env", args[0], 4) == 0)
			ft_env(env, &env_list);
		else if (strcmp("pwd", args[0]) == 0)
			pwd();
		else if (strcmp(args[0], "cd") == 0)
			cd(args);
		else if (strcmp(args[0], "export") == 0)
		{
			export(args, env, &env_list);
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			free(rl);
			free(args);
			exit(0);
		}
		if (!args)
			continue;
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
		return 1;
	return 0;
}
