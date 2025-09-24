/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:03:53 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/24 15:05:01 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	raycasting_loop(t_game *game, t_player *player)
{
	double		camera_x;
	int			i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		camera_x = 2 * i / (double)WINDOW_WIDTH - 1;
		game->ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
		game->ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
		cast_single_ray(player, game, i);
		i++;
	}
}

static void	render_frame(t_game *game)
{
	int		x;
	int		y;

	clear_image(game);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (game->texture_pixels[y][x] > 0)
				put_pixel(x, y, game->texture_pixels[y][x], game);
			else if (y < WINDOW_HEIGHT / 2)
				put_pixel(x, y, game->ceiling_color, game);
			else
				put_pixel(x, y, game->floor_color, game);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	draw_loop(t_game *game)
{
	t_player	*player;

	if (!game || !game->ray)
		return (0);
	player = &game->player;
	move_player(player, game);
	init_texture_pixels(game);
	raycasting_loop(game, player);
	render_frame(game);
	return (1);
}

void	init_player(t_player *player)
{
	player->x = 22 * BLOCK;
	player->y = 12 * BLOCK;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

t_vline	prepare_vline(int x, t_raycast *r)
{
	t_vline	vline;

	vline.x = x;
	vline.start = r->draw_start;
	vline.end = r->draw_end;
	vline.side = r->side;
	return (vline);
}
