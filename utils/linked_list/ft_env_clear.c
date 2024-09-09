#include "minishell.h"

void ft_env_clear(t_env **lst)
{
	t_env	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}
