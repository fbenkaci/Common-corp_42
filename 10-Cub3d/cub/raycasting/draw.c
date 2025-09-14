/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:20:15 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/14 18:12:33 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Dessine une ligne verticale à l'écran
** x: position horizontale de la ligne
** start: position verticale de début
** end: position verticale de fin
** side: indique si c'est un mur N/S (0) ou E/W (1) pour l'ombrage
*/

static int	select_texture(t_game *game, t_vline vline)
{
	if (vline.side == 0)
	{
		if (game->ray->dir_x > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (game->ray->dir_y > 0)
			return (2);
		else
			return (3);
	}
}

void	draw_vertical_line(t_game *game, t_vline vline)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;
	int		tex_num;

	tex_num = select_texture(game, vline);
	step = 1.0 * TEX_HEIGHT / (vline.end - vline.start);
	tex_pos = (vline.start - WINDOW_HEIGHT / 2 + (vline.end - vline.start) / 2)
		* step;
	y = 0;
	while (y < vline.start)
		put_pixel(vline.x, y++, game->ceiling_color, game);
	while (y < vline.end)
	{
		game->tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_texture_color(&game->texture[tex_num], game->tex_x,
				game->tex_y);
		if (vline.side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(vline.x, y++, color, game);
	}
	while (y < WINDOW_HEIGHT)
		put_pixel(vline.x, y++, game->floor_color, game);
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	int		index;
	int		color;
	char	*ptr;

	if (x >= texture->width || y >= texture->height || x < 0 || y < 0)
		return (0);
	index = y * texture->size_line + x * (texture->bpp / 8);
	ptr = texture->data + index;
	color = *(int *)ptr;
	return (color);
}

// Initialize map-related structures and player
void	setup_map_and_player(t_game *game)
{
	if (!game->data.map)
	{
		cleanup(game);
		exit(1);
	}
	game->map_info.data = game->data.map;
	game->map_info.height = 0;
	while (game->data.map[game->map_info.height])
		game->map_info.height++;
	game->map_info.width = ft_strlen(game->data.map[0]);
	init_player(&game->player);
	find_player_start(game);
}
