#include "minishell.h"



void	prompt(char **env)
{
	char	*rl;
	t_list *list;
	// t_cmd *cmd;

	list = NULL;
	// cmd = NULL;
	while (1)
	{
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		lexer(rl, &list);
		syntax_error(list);
		if (strncmp("env", rl, 4) == 0)
			ft_env(env);
		else if (strcmp(rl, "cd") == 0)
			cd(ft_split(rl, ' '));
		else if (strcmp("pwd", rl) == 0)
			print_working_directory();
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
