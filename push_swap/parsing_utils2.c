/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:23:14 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 15:38:31 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_duplicate_nb(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_elemt)
	{
		j = i + 1;
		while (j < data->nb_elemt)
		{
			if (data->nb[i] - data->nb[j] == 0)
			{
				write(2, "Error\nThere is duplicate number.\n", 34);
				free_map(data->dest);
				free(data->nb);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_free(t_data *data)
{
	free_map(data->dest);
	free(data->nb);
}

int	has_spaces(char *str)
{
	return (ft_strchr(str, ' ') != NULL);
}
