#include "minishell.h"

t_global	g_mini;


void free_array(char **array)
{
    int i;

    if (!array)
        return;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

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
void debug_list(t_list *list)
{
    while (list)
    {
       // printf("Node content: %s\n", list->content);
        list = list->next;
    }
}

void	prompt(char **env)
{
	char	*rl;
	t_list	*list;
	t_env	*env_list;

	env_list = NULL;
	list = NULL;
	ft_env(env, &env_list);
	g_mini.env = env_list;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_mini.sig_flag = 0;
		g_mini.command = malloc(sizeof(t_cmd));
		g_mini.command->cmd = NULL;
		g_mini.command->files = NULL;
		g_mini.command->next = NULL;
		signal(SIGINT, handle_sigint);
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (empty_prompt(rl) == 0)
		{
			free(rl);
			continue ;
		}
		lexer(rl, &list);
		if(!syntax_error(list))
		{
			expand(env_list, &list);
			parser(list);
			run_heredoc(g_mini.command);
			// run_cmd(g_mini.command, env_list, env_list);
			if (g_mini.command->cmd[0] != NULL)
				execution(g_mini.command);
		}
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
}
