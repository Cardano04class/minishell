#include "minishell.h"

#include <stdio.h>

void ft_print_env(char **env)
{
    int i = 0;

    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}


void	ft_prompt(char **env)
{
	char	*rl;
	t_list *list;
	list = NULL;
	while (1)
	{
		rl = readline("minishell$ ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		lexer(rl, &list);
		// ft_lstdisplay(list);
		syntax_error(list);
		ft_print_env(env);
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
		ft_prompt(env);
	else	
		return 1;
	return 0;
}
