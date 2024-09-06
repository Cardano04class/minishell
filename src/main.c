#include "minishell.h"

void ft_prompt(void)
{
    
    char *rl;
    while(1)
    {
        rl = readline("minishell$> ");
        if(rl == NULL)
            exit(1);
        lexer(rl);
        add_history(rl);
    }
    rl_clear_history();
}

int	main(int ac, char **av)
{
    av = NULL;
    if (ac == 1)
    {
        ft_prompt();
    }
}
