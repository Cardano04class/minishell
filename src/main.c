#include "../includes/minishell.h"

int main(int ac, char **av)
{
    av = NULL;
    if (ac == 1)
    {
        while(1)
        {
            printf("alo\n");
            sleep(2);
        }
    }
}