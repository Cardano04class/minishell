#include "minishell.h"

t_global g_mini;

void	prompt(char **env)
{
	char	*rl;
	t_list	*list;
	char	**args;
	list = NULL;
	g_mini.command = malloc(sizeof(t_cmd));
	g_mini.command->files = NULL;
	g_mini.command->heredoc = NULL;
	g_mini.command->next = NULL;
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
			ft_env(env);
		else if (strcmp("pwd", args[0]) == 0)
			print_working_directory();
		else if (strcmp("echo", args[0]) == 0)
			echo(args);
		else if (strcmp(args[0], "cd") == 0)
			cd(args);
		else
			printf("Command not found\n");
		//ft_lstdisplay(list);
		parser(list);
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
