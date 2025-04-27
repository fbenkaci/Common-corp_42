/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:01:21 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/27 15:44:08 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**allocate_joined(char **result, char **new_data, int *len_result,
		int *len_new_data)
{
	char	**joined;

	*len_result = 0;
	*len_new_data = 0;
	while (result && result[*len_result])
		(*len_result)++;
	while (new_data && new_data[*len_new_data])
		(*len_new_data)++;
	joined = malloc(sizeof(char *) * (*len_result + *len_new_data + 1));
	if (!joined)
		return (NULL);
	return (joined);
}

static void	fill_joined(char **joined, char **result, char **new_data,
		int len_result)
{
	int	i;
	int	j;

	i = 0;
	while (i < len_result)
	{
		joined[i] = result[i];
		i++;
	}
	j = 0;
	while (new_data && new_data[j])
	{
		joined[i] = ft_strjoin(joined[i - 1], new_data[j]);
		i++;
		j++;
	}
	joined[i] = NULL;
}

char	**strjoin_tab(char **result, char **new_data)
{
	char	**joined;
	int		len_result;
	int		len_new_data;

	joined = allocate_joined(result, new_data, &len_result, &len_new_data);
	if (!joined)
		return (NULL);
	fill_joined(joined, result, new_data, len_result);
	return (joined);
}
