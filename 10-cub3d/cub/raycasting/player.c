/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:03:02 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/21 16:38:16 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Cette fonction gère tous les mouvements du joueur :
** 1. Déplacement avant/arrière (W/S) en utilisant le vecteur de direction
** 2. Déplacement latéral (A/D) en utilisant le vecteur du plan de caméra
** 3. Rotation de la caméra (Flèches) en appliquant une matrice de rotation 2D
**    aux vecteurs de direction et du plan de caméra
*/

static void	move_forward(t_player *player, t_game *game, double speed)
{
	double	max_dist;
	double	actual_speed;

	max_dist = calculate_collision_distance(player, game, player->dir_x, 0);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->x += player->dir_x * actual_speed;
	max_dist = calculate_collision_distance(player, game, 0, player->dir_y);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->y += player->dir_y * actual_speed;
}

static void	move_backward(t_player *player, t_game *game, double speed)
{
	double	max_dist;
	double	actual_speed;

	max_dist = calculate_collision_distance(player, game, -player->dir_x, 0);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->x -= player->dir_x * actual_speed;
	max_dist = calculate_collision_distance(player, game, 0, -player->dir_y);
	actual_speed = fmin(speed, max_dist);
	if (actual_speed > 0)
		player->y -= player->dir_y * actual_speed;
}

static void	move_forward_backward(t_player *player, t_game *game, double speed)
{
	if (player->key_up)
		move_forward(player, game, speed);
	if (player->key_down)
		move_backward(player, game, speed);
}

static void	move_right(t_player *player, t_game *game, double speed)
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

static void	move_left(t_player *player, t_game *game, double speed)
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

static void	move_left_right(t_player *player, t_game *game, double speed)
{
	if (player->key_right)
		move_right(player, game, speed);
	if (player->key_left)
		move_left(player, game, speed);
}

static void	rotate_left(t_player *player, double rot_speed)
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

static void	rotate_right(t_player *player, double rot_speed)
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

void	move_player(t_player *player, t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 5;
	rot_speed = 0.05;
	move_forward_backward(player, game, move_speed);
	move_left_right(player, game, move_speed);
	if (player->left_rotate)
		rotate_left(player, rot_speed);
	if (player->right_rotate)
		rotate_right(player, rot_speed);
}
