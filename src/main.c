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
	ft_env(env, &env_list);
	while (1)
	{
		g_mini.command = malloc(sizeof(t_cmd));
		g_mini.command->files = NULL;
		g_mini.command->heredoc = NULL;
		g_mini.command->next = NULL;
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
		//ft_lstdisplay(list);
		parser(list);
		// t_cmd *tmp = g_mini.command;
		// while (tmp->files != NULL)
		// {
		// 	printf("files : %s\n", tmp->files->filename);
		// 	tmp->files = tmp->files->next;
		// }
		// printf("test %p\n", g_mini.command->files);
		run_cmd(g_mini.command, env_list);
		ft_lstclear(&list);
		add_history(rl);
		free(rl);
		free(args);
	}
	//rl_clear_history();
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