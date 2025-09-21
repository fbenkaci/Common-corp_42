/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:03:53 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/20 16:17:45 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	draw_loop(t_game *game)
{
	float		ray_angle;
	double		camera_x;
	t_player	*player;
	int			i;

	if (!game || !game->ray)
		return (0);
	i = 0;
	player = &game->player;
	ray_angle = 0;
	move_player(player, game);
	clear_image(game);
	while (i < WINDOW_WIDTH)
	{
		camera_x = 2 * i / (double)WINDOW_WIDTH - 1;
		game->ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
		game->ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
		ray_angle = atan2(game->ray->ray_dir_y, game->ray->ray_dir_x);
		draw_line(player, game, ray_angle, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->data.map[y][x] == '1')
		return (true);
	return (false);
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
