/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:30:00 by waldozoo          #+#    #+#             */
/*   Updated: 2025/09/24 15:21:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_pixels(t_game *game)
{
	int	i;

	if (game->texture_pixels)
		free_texture_pixels(game);
	game->texture_pixels = ft_calloc(WINDOW_HEIGHT + 1, sizeof(int *));
	if (!game->texture_pixels)
		return ;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->texture_pixels[i] = ft_calloc(WINDOW_WIDTH + 1, sizeof(int));
		if (!game->texture_pixels[i])
			return ;
		i++;
	}
}

void	free_texture_pixels(t_game *game)
{
	int	i;

	if (!game->texture_pixels)
		return ;
	i = 0;
	while (i < WINDOW_HEIGHT && game->texture_pixels[i])
	{
		free(game->texture_pixels[i]);
		i++;
	}
	free(game->texture_pixels);
	game->texture_pixels = NULL;
}

static int	get_texture_index(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (2);
		else
			return (3);
	}
}

static void	draw_textured_column(t_game *game, t_raycast *ray, int x,
		int tex_index)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		game->tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_texture_color(&game->texture[tex_index], game->tex_x,
				game->tex_y);
		if (tex_index == 3 || tex_index == 0)
			color = (color >> 1) & 8355711;
		if (color > 0)
			game->texture_pixels[y][x] = color;
		y++;
	}
}

void	update_texture_pixels(t_game *game, t_raycast *ray, int x)
{
	int	tex_index;

	tex_index = get_texture_index(ray);
	game->tex_x = (int)(game->wall_x * TEX_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y > 0))
		game->tex_x = TEX_WIDTH - game->tex_x - 1;
	draw_textured_column(game, ray, x, tex_index);
}
