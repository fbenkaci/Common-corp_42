/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:43:10 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/19 14:34:48 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_objects(t_data *map, char object)
{
	int	count;
	int	x;
	int	y;

	if (!map || !map->grid)
		return (0);
	count = 0;
	y = 0;
	while (map->grid[y] != NULL)
	{
		x = 0;
		while (map->grid[y][x] != '\0')
		{
			if (map->grid[y][x] != '1' && map->grid[y][x] != '0'
				&& map->grid[y][x] != 'P' && map->grid[y][x] != 'E'
				&& map->grid[y][x] != 'C')
				return (0);
			if (map->grid[y][x] == object)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	check_map_objects(t_data *map)
{
	map->start = count_objects(map, 'P');
	map->item = count_objects(map, 'C');
	map->exit = count_objects(map, 'E');
	if (map->start != 1 || map->exit != 1)
	{
		ft_printf("Error\n");
		ft_printf("Il doit y avoir une seule position ");
		ft_printf("de départ une seule sortie.\n");
		ft_printf("Aucun élément autre que '1', '0',");
		ft_printf("'E','P' ou 'C' n'est permis.\n");
		free_map(map->grid);
		free_map(map->cpy_grid);
		return (0);
	}
	if (map->item < 1)
	{
		ft_printf("Error.\nIl doit y avoir au moins 1 item (C).\n");
		free_map(map->grid);
		free_map(map->cpy_grid);
		return (0);
	}
	return (1);
}

int	check_map_rectangle(t_data *map)
{
	int	size_line;
	int	y;
	int	x;

	if (!map || !map->grid || !map->grid[0])
		return (0);
	size_line = 0;
	while (map->grid[0][size_line] != '\0')
		size_line++;
	y = 1;
	while (map->grid[y] != NULL)
	{
		x = 0;
		while (map->grid[y][x] != '\0')
			x++;
		if (x != size_line)
		{
			ft_printf("Error.\nLa map n'est pas rectangulaire.\n");
			free_map(map->grid);
			free_map(map->cpy_grid);
			return (0);
		}
		y++;
	}
	return (1);
}

int	check_valid_col_row(t_data *map, int last_col, int last_row, int x)
{
	int	y;

	y = 0;
	if (!map || !map->grid)
		return (0);
	while (map->grid[0][x] != '\0')
	{
		if (map->grid[0][x] != '1')
			return (0);
		x++;
	}
	x = 0;
	while (map->grid[last_row][x] != '\0')
	{
		if (map->grid[last_row][x] != '1')
			return (0);
		x++;
	}
	while (map->grid[y] != NULL)
	{
		if (map->grid[y][0] != '1' || map->grid[y][last_col] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	check_map_borders(t_data *map)
{
	int	last_col;
	int	last_row;
	int	x;

	last_col = 0;
	last_row = 0;
	x = 0;
	while (map->grid[last_row] != NULL)
		last_row++;
	last_row--;
	while (map->grid[0][last_col] != '\0')
		last_col++;
	last_col--;
	if (!check_valid_col_row(map, last_col, last_row, x))
	{
		ft_printf("Error.\nLes murs ne sont pas bon.\n");
		return (0);
	}
	return (1);
}
