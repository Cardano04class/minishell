#include "minishell.h"

int main(int ac, char **av)
{
    char prompt[] = "minishell$>";
    av = NULL;
    if (ac == 1)
    {
        while(1)
        {
            printf("%s\n", prompt);
            sleep(2);
        }
    }
}