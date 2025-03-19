/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:40:01 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/09 10:29:08 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_data *map, char **cpy_grid, int y, int x)
{
	if (y < 0 || x < 0 || y >= map->total_rows || x >= map->total_cols)
		return ;
	if (map->cpy_grid[y][x] == '1' || map->cpy_grid[y][x] == 'V')
		return ;
	if (map->cpy_grid[y][x] == 'C')
		map->item -= 1;
	if (map->cpy_grid[y][x] == 'E' && map->item != 0)
		return ;
	map->cpy_grid[y][x] = 'V';
	flood_fill(map, cpy_grid, y + 1, x);
	flood_fill(map, cpy_grid, y - 1, x);
	flood_fill(map, cpy_grid, y, x + 1);
	flood_fill(map, cpy_grid, y, x - 1);
}

int	is_path_valid(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->total_rows)
	{
		j = 0;
		while (j < map->total_cols)
		{
			if (map->cpy_grid[i][j] == 'C' || map->cpy_grid[i][j] == 'P'
				|| map->cpy_grid[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_path(t_data *map)
{
	int				x;
	int				y;
	unsigned int	nb_item;

	nb_item = map->item;
	map->total_rows = 0;
	while (map->cpy_grid[map->total_rows] != NULL)
		map->total_rows++;
	map->total_cols = ft_strlen(map->cpy_grid[0]);
	coordonne_player(map);
	x = map->player_x;
	y = map->player_y;
	flood_fill(map, map->cpy_grid, y, x);
	if (!is_path_valid(map))
	{
		free_map(map->grid);
		free_map(map->cpy_grid);
		ft_printf("Error.\nIl n'y a pas de chemin valide.\n");
		return (0);
	}
	map->item = nb_item;
	return (1);
}

void	mlx_error(t_data img)
{
	free_map(img.grid);
	free_map(img.cpy_grid);
	ft_printf("Error.\nmlx_init() a échoué.\n");
}
