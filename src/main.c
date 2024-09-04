#include "minishell.h"

void ft_prompt(void)
{
    
    char *rl;
    while(1)
    {
        rl = readline("minishell$>");
        lexer(&rl);
    }
}

int	main(int ac, char **av)
{
    av = NULL;
    if (ac == 1)
    {
        ft_prompt();
    }
}
