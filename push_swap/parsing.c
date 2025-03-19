/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:08:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 12:35:11 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_if_numbers(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j])
		{
			while (av[i][j] == ' ')
				j++;
			if (av[i][j] == '\0')
				break ;
			if (check_if_digit(av, i, j) != 0)
				return (1);
			if (check_sign(av, i, j) != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_doublon(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = i + 1;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) == 0)
			{
				write(2, "Error\nThere is duplicate number.\n", 34);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_doublon_string(char **av, t_data *data)
{
	int	i;

	i = 1;
	data->nb_elemt = 0;
	av[1] = remove_extra_spaces(av[1]);
	data->dest = ft_split(av[1], ' ');
	if (!data->dest)
		return (1);
	while (data->dest[data->nb_elemt] != NULL)
		data->nb_elemt++;
	data->nb = malloc(data->nb_elemt * sizeof(int));
	if (!data->nb)
	{
		free_map(data->dest);
		return (1);
	}
	if (convert_to_int(data) == 1)
	{
		ft_free(data);
		return (1);
	}
	if (check_duplicate_nb(data) == 1)
		return (1);
	ft_free(data);
	return (0);
}
