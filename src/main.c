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
	char	**args;
	t_env *env_list = NULL;
	
	list = NULL;
	g_mini.command = malloc(sizeof(t_cmd));
	g_mini.command->files = NULL;
	g_mini.command->heredoc = NULL;
	g_mini.command->next = NULL;
	ft_env(env, &env_list);
	while (1)
	{
		rl = readline("minishell$ ");
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
		args = ft_split(rl, ' ');
		lexer(rl, &list);
		syntax_error(list);
		if (strncmp("env", args[0], 4) == 0)
		{
			ft_env(env,&env_list);
			print_env(env_list);
		}
		else if (strcmp("pwd", args[0]) == 0)
			pwd();
		else if (strcmp("echo", args[0]) == 0)
			echo(args);
		else if (strcmp(args[0], "cd") == 0)
			cd(args);
		else if (strcmp(args[0], "export") == 0)
			export(args, &env_list);
		else if (strcmp(args[0], "unset") == 0)
			unset(args, &env_list);
		else if (strcmp(args[0], "exit") == 0)
		{
			free(rl);
			free(args);
			exit(0);
		}
		else
			printf("%s: Command not found\n", rl);
		// ft_lstdisplay(list);
		parser(list);
		ft_lstclear(&list);
		add_history(rl);
		free(rl);
		free(args);
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
