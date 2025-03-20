/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:08:44 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/20 15:59:08 by fbenkaci         ###   ########.fr       */
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

// int	check_doublon(char **av, t_data *data)
// {
// 	int	i;

// 	i = 1;
// 	data->j = 0;
// 	ft_printf("%s", av[i]);
// 	// ft_printf("qq");
// 	data->nb[data->j] = ft_atoi(av[i]);
// 	ft_printf("%d\n", data->nb[data->j]);
// 	data->j++;
// 	i++;
// ft_printf("qq");
// ft_printf("%d\n", data->nb);
// int	i;
// int	j;
// i = 1;
// while (i < ac)
// {
// 	j = i + 1;
// 	while (j < ac)
// 	{
// 		if (is_valid_int(av[i]) == 1)
// 			return (1);
// 		if (ft_strcmp(av[i], av[j]) == 0)
// 		{
// 			write(2, "Error\nThere is duplicate number.\n", 34);
// 			return (1);
// 		}
// 		j++;
// 	}
// 	i++;
// }
// 	return (0);
// }

int	count_words(t_data *data)
{
	int	i;

	i = 0;
	while (data->tmp[i] != NULL)
		i++;
	return (i);
}

void	nb_argument(char **av, t_data *data)
{
	int	i;

	i = 1;
	data->nb_elemt = 0;
	while (av[i])
	{
		if (has_spaces(av[i]))
		{
			data->tmp = ft_split(av[i], ' ');
			if (!data->tmp)
				return ;
			data->nb_elemt += count_words(data);
			free_map(data->tmp);
		}
		else
			data->nb_elemt++;
		i++;
	}
}

int	check_doublon_string(char **av, t_data *data)
{
	int	i;
	int	j;
	int	index;

	i = 1;
	index = 0;
	ft_printf("1ok\n");
	nb_argument(av, data);
	data->dest = malloc((data->nb_elemt + 1) * sizeof(char *));
	if (!data->dest)
		return (1);
	printf("2ok\n");
	while (av[i] != NULL)
	{
		printf("3ok\n");
		if (has_spaces(av[i]) == 0)
		{
			printf("4ok\n");

			data->tmp = ft_split(av[i], ' ');
			if (!data->tmp)
				return (1);
			j = 0;
			while (data->tmp[j] != NULL)
			{
				data->dest[index++] = ft_strdup(data->tmp[j]);
				j++;
			}
			free_map(data->tmp);
		}
		else
			data->tmp[index++] = ft_strdup(av[i]);
		i++;
	}
	data->dest[index] = NULL;
	data->nb = malloc(data->nb_elemt * sizeof(int));
	if (!data->nb)
	{
		free_map(data->dest);
		return (1);
	}
	if (convert_to_int(data) == 1 || check_duplicate_nb(data) == 1)
	{
		ft_free(data);
		return (1);
	}
	return (0);
}
