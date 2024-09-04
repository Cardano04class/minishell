#include "minishell.h"

int ft_isspace(int c)
{
	if(c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == 32)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
    int		i;
	int		j;
	t_list	**lst;

	j = 0;
    while (av[j] != NULL)
	{
		i = 0;
		while (av[j][i] != '\0')
		{
			if (av[j][i] == 34 || av[j][i] == 39 || ft_isspace(av[j][i])) // 34 for (") and 39 for (').
				i++;
			else if (av[j][i] == '|')
			{
				ft_lstaddback(lst, ft_lstnew("|", PIPE));
			}
			else if (av[j][i] == '>')
			{
				ft_lstaddback(lst, ft_lstnew(">", INRED));
			}
			else if (av[j][i] == '<')
			{
				ft_lstaddback(lst, ft_lstnew("<", OUTRED));
			}
			else if (av[j][i] == '>' && av[j][i + 1] == '>')
			{
				ft_lstaddback(lst, ft_lstnew(">>", APPEND));
			}
			else if (av[j][i] == '<' && av[j][i] == '<')
			{
				ft_lstaddback(lst, ft_lstnew("|", HEREDOC));
			}
			else
			{

			}
		}
		j++;
	}
}

