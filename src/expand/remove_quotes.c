/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:38:15 by mamir             #+#    #+#             */
/*   Updated: 2024/11/16 15:38:25 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quotes(char *str, size_t *i, size_t *j, char *result,
		int *in_quotes)
{
	if (str[*i] == '\'' && !in_quotes[1])
		in_quotes[0] = !in_quotes[0];
	else if (str[*i] == '\"' && !in_quotes[0])
		in_quotes[1] = !in_quotes[1];
	else
		result[(*j)++] = str[*i];
	(*i)++;
}

char	*remove_quotes(char *str)
{
	char	*result;
	size_t	i;
	size_t	j;
	int		in_quotes[2] = {0, 0};

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
		process_quotes(str, &i, &j, result, in_quotes);
	result[j] = '\0';
	return (result);
}
