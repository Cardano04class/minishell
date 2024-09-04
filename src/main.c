#include "../includes/minishell.h"

int main(int ac, char **av)
{
    int		i;
	int		j;

	j = 0;
    while (av[j] != NULL)
	{
		i = 0;
		while (av[j][i] != '\0')
		{
			if (av[j][i] == 34 || av[j][i] == 39 || av[j][i] == ' ' || av[j][i] == '	') // 34 for (") and 39 for (').
				i++;
			else if (av[j][i] == '|')
			{
				
			}
			else if (av[j][i] == '>')
			{
			}
			else if (av[j][i] == '<')
			{
			}
			else if (av[j][i] == '>>')
			{
			}
			else if (av[j][i] == '<<')
			{
			}
			else
			{
			}
		}
		j++;
	}
}