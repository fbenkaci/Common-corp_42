/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:08:20 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/24 15:09:51 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y
		* sin(-rot_speed);
	player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y
		* cos(-rot_speed);
	player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y
		* sin(-rot_speed);
	player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y
		* cos(-rot_speed);
}

void	rotate_right(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y
		* sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y
		* sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y
		* cos(rot_speed);
}

void	move_right(t_player *player, t_game *game, double speed)
{
	double	max_dist;
	double	actual_speed;

	max_dist = calculate_collision_distance(player, game, player->plane_x, 0);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->x += player->plane_x * actual_speed;
	max_dist = calculate_collision_distance(player, game, 0, player->plane_y);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->y += player->plane_y * actual_speed;
}

void	move_left(t_player *player, t_game *game, double speed)
{
	double	max_dist;
	double	actual_speed;

	max_dist = calculate_collision_distance(player, game, -player->plane_x, 0);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->x -= player->plane_x * actual_speed;
	max_dist = calculate_collision_distance(player, game, 0, -player->plane_y);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->y -= player->plane_y * actual_speed;
}
