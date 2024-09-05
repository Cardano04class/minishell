#include "minishell.h"
#include <linux/limits.h>

void ft_prompt(char **av)
{
    av = NULL;
    char *rl;
    while(1)
    {
        rl = readline("minishell$> ");
        printf("\n");
		lexer(rl);
        printf("\n");
    }
}

int	main(int ac, char **av)
{
    if (ac == 1)
    {
        ft_prompt(av);
    }
}
