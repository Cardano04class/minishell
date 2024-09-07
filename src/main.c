#include "minishell.h"

void	ft_prompt(void)
{
	char	*rl;
	t_list *list;

	list = NULL;
	while (1)
	{
		rl = readline("minishell$>");
		if (rl == NULL)
		{
			free(rl);
			printf("exit\n");
			exit(1);
		}
		lexer(rl, &list);
		// ft_lstdisplay(list);
		syntax_error(list);
		ft_lstclear(&list);
		add_history(rl);
	}
	rl_clear_history();
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
		ft_prompt();
	else	
		return 1;
	return 0;
}
