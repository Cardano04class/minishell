#include "minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new;

	new = _malloc(sizeof(t_env), 'm');
	if (!new)
        return NULL;
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
