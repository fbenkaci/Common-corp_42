/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:03:02 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/14 18:11:23 by fbenkaci         ###   ########.fr       */
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

static void	move_forward_backward(t_player *player, t_game *game, double speed)
{
	double	next_x;
	double	next_y;

	if (player->key_up)
	{
		next_x = player->x + player->dir_x * speed;
		next_y = player->y + player->dir_y * speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
	if (player->key_down)
	{
		next_x = player->x - player->dir_x * speed;
		next_y = player->y - player->dir_y * speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
}

static void	move_left_right(t_player *player, t_game *game, double speed)
{
	double	next_x;
	double	next_y;

	if (player->key_right)
	{
		next_x = player->x + player->plane_x * speed;
		next_y = player->y + player->plane_y * speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
	if (player->key_left)
	{
		next_x = player->x - player->plane_x * speed;
		next_y = player->y - player->plane_y * speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
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
