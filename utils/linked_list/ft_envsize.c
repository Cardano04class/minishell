#include "minishell.h"

int	ft_envsize(t_env *env)
{
	int	count;

	count = 0;
	if (env == NULL)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		count++;
	}
	return (count);
}