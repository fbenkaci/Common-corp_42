/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:01:21 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/04/12 13:10:09 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	strlen_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (!tab || !tab[i])
// 		return (0);
// 	while (tab && tab[i])
// 		i++;
// 	return (i);
// }

char	**strjoin_tab(char **result, char **new_data)
{
	int		len_result;
	int		len_new_data;
	char	**joined;
	int		i;
	int		j;

	len_result = 0;
	len_new_data = 0;
	while (result && result[len_result])
		len_result++;
	while (new_data && new_data[len_new_data])
		len_new_data++;
	joined = malloc((sizeof(char *)) * (len_result + len_new_data + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < len_result)
	{
		joined[i] = result[i];
		i++;
	}
	j = 0;
	while (j < len_new_data)
	{
		joined[i] = ft_strjoin(joined[i - 1], new_data[j]);
		i++;
        j++;
	}
	joined[i] = NULL;
	return (joined);
}
