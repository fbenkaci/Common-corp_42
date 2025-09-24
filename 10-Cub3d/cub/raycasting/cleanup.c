/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:06:11 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/13 19:14:45 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_game *game)
{
	if (game->close)
		return (0);
	game->close = 1;
	cleanup(game);
	exit(0);
	return (0);
}

void	free_map(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

/*
** Nettoie la mémoire avant de quitter
*/

static void	free_maps(t_game *game)
{
	int	i;

	if (game->data.file)
		free_map(game->data.file);
	if (game->data.file2)
		free_map(game->data.file2);
	if (game->data.map)
	{
		i = 0;
		while (game->data.map[i])
		{
			free(game->data.map[i]);
			i++;
		}
		free(game->data.map);
	}
}

void	cleanup(t_game *game)
{
	int	i;

	if (game->ray)
		free(game->ray);
	free_texture_pixels(game);
	free_maps(game);
	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}
