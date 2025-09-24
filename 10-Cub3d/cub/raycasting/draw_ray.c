/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:16:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/21 16:19:44 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_raycast *r, t_player *player, t_game *game)
{
	r->pos_x = player->x / BLOCK;
	r->pos_y = player->y / BLOCK;
	r->ray_dir_x = game->ray->ray_dir_x;
	r->ray_dir_y = game->ray->ray_dir_y;
	r->map_x = (int)r->pos_x;
	r->map_y = (int)r->pos_y;
	if (r->ray_dir_x == 0.0f)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0f / r->ray_dir_x);
	if (r->ray_dir_y == 0.0f)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0f / r->ray_dir_y);
	r->hit = 0;
}

static void	init_step(t_raycast *r)
{
	if (r->ray_dir_x < 0.0f)
	{
		r->step_x = -1;
		r->side_dist_x = (r->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0f - r->pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0.0f)
	{
		r->step_y = -1;
		r->side_dist_y = (r->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0f - r->pos_y) * r->delta_dist_y;
	}
}

static void	perform_dda(t_raycast *r, t_game *game)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_y >= 0 && r->map_x >= 0 && r->map_y < game->map_info.height
			&& r->map_x < (int)ft_strlen(game->data.map[r->map_y])
			&& game->data.map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

/* Compute perpendicular distance, line start/end and texture X */
static void	compute_wall_distance(t_raycast *r, t_player *player, t_game *game)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
	r->line_height = (int)(WINDOW_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + WINDOW_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WINDOW_HEIGHT / 2;
	if (r->draw_end >= WINDOW_HEIGHT)
		r->draw_end = WINDOW_HEIGHT - 1;
	if (r->side == 0)
		game->wall_x = (player->y / BLOCK) + r->perp_wall_dist * r->ray_dir_y;
	else
		game->wall_x = (player->x / BLOCK) + r->perp_wall_dist * r->ray_dir_x;
	game->wall_x -= floor(game->wall_x);
}

/* Cast a single ray and update texture pixels */

void	cast_single_ray(t_player *player, t_game *game, int x)
{
	t_raycast	r;

	init_ray(&r, player, game);
	init_step(&r);
	perform_dda(&r, game);
	compute_wall_distance(&r, player, game);
	update_texture_pixels(game, &r, x);
}
