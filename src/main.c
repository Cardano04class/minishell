#include "minishell.h"
#include <linux/limits.h>

void ft_prompt(char **av)
{
    av = NULL;
    char *rl;
    while(1)
    {
        rl = readline("minishell$>");
        printf("%s\n", rl);
    }
}

int	main(int ac, char **av)
{
    if (ac == 1)
    {
        ft_prompt(av);
    }
}
