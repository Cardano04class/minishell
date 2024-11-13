#include "includes/minishell.h"


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int main()
{
    char *line;
    char delimiter[] = "d";

    while (1)
    {
        line = readline(">");
        printf("%s", line);
        if (ft_strcmp(line, delimiter) == 0)
            break ;
    }
}