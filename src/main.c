#include "minishell.h"

void print_env(t_env *env)
{
	while(env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void ft_env(char **env)
{
	t_env *lst;
	t_env *node;

	lst = NULL;
	int i = 0;
	while (env[i])
	{
		char *equal_sign;

		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			node = ft_env_new(env[i], equal_sign + 1);
			*equal_sign = '=';
			if (node)
				ft_env_addback(&lst, node);
		}
		i++;
	}
	print_env(lst);
}

void	prompt(char **env)
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
		syntax_error(list);
		ft_env(env);
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
