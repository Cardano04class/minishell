#include "minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
        return NULL;
    new->key = ft_strdup(key);
    if (!new->key)
    {
        free(new);
        return NULL;
    }
    new->value = ft_strdup(value);
    if (!new->value)
    {
        free(new);
        return NULL;
    }
	new->next = NULL;
	return (new);
}
