/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:03:02 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/11 18:21:39 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Cette fonction initialise les propriétés du joueur :
** - Position initiale dans la carte (x, y)
** - Vecteur de direction (dir_x, dir_y) qui indique où le joueur regarde
** - Plan de caméra (plane_x, plane_y) qui définit le champ de vision
** - États des touches pour le contrôle du mouvement
*/
void	init_player(t_player *player)
{
	// Position initiale du joueur dans la carte (en pixels)
	player->x = 22 * BLOCK;
	player->y = 12 * BLOCK;
	// Vecteur de direction initial : le joueur regarde vers le nord
	player->dir_x = 0;
	player->dir_y = -1;
	// Plan de caméra perpendiculaire au vecteur de direction
	// La valeur 0.66 représente environ un FOV de 66 degrés
	player->plane_x = 0.66;
	player->plane_y = 0;
	// Initialisation des états des touches à faux
	player->key_up = false;    // W - Avancer
	player->key_down = false;  // S - Reculer
	player->key_right = false; // D - Pas à droite
	player->key_left = false;  // A - Pas à gauche
	// États des touches de rotation
	player->left_rotate = false;  // Flèche gauche
	player->right_rotate = false; // Flèche droite
}

int	key_press(int keycode, t_game *game)
{
	t_player *player;

	player = &game->player;
	
	if (keycode == 65307) // ESC key
		close_window(game);
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

/*
** Cette fonction gère tous les mouvements du joueur :
** 1. Déplacement avant/arrière (W/S) en utilisant le vecteur de direction
** 2. Déplacement latéral (A/D) en utilisant le vecteur du plan de caméra
** 3. Rotation de la caméra (Flèches) en appliquant une matrice de rotation 2D
**    aux vecteurs de direction et du plan de caméra
*/
void	move_player(t_player *player, t_game *game)
{
	double	next_x;
	double	next_y;

	// double	next_x;
	// double	next_y;
	double move_speed;  // Vitesse de déplacement
	double rot_speed;   // Vitesse de rotation
	double old_dir_x;   // Stockage temporaire pour la rotation
	double old_plane_x; // Stockage temporaire pour la rotation
	// Définition des vitesses de mouvement et de rotation
	// Ces valeurs peuvent être ajustées pour un contrôle plus fluide
	move_speed = 5;
	rot_speed = 0.05;
	// Mouvement avant (W)
	// Déplace le joueur dans la direction où il regarde
	if (player->key_up)
	{
		next_x = player->x + player->dir_x * move_speed;
		next_y = player->y + player->dir_y * move_speed;
		// Vérifie d'abord Y puis X séparément pour permettre de glisser le long des murs
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
	// Mouvement arrière (S)
	// Déplace le joueur dans la direction opposée à où il regarde
	if (player->key_down)
	{
		next_x = player->x - player->dir_x * move_speed;
		next_y = player->y - player->dir_y * move_speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
	// Mouvement latéral droit (D)
	// Utilise le vecteur du plan de caméra pour un déplacement perpendiculaire
	if (player->key_right)
	{
		next_x = player->x + player->plane_x * move_speed;
		next_y = player->y + player->plane_y * move_speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
	// Mouvement latéral gauche (A)
	// Utilise le vecteur du plan de caméra dans la direction opposée
	if (player->key_left)
	{
		next_x = player->x - player->plane_x * move_speed;
		next_y = player->y - player->plane_y * move_speed;
		if (game->data.map[(int)(player->y / BLOCK)][(int)(next_x
				/ BLOCK)] != '1')
			player->x = next_x;
		if (game->data.map[(int)(next_y / BLOCK)][(int)(player->x
				/ BLOCK)] != '1')
			player->y = next_y;
	}
	// Rotation vers la gauche (Flèche gauche)
	// Applique une matrice de rotation 2D dans le sens anti-horaire
	if (player->left_rotate)
	{
		// Rotation du vecteur de direction
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y
			* sin(-rot_speed);
		player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y
			* cos(-rot_speed);
		// Rotation du plan de caméra (doit rester perpendiculaire à la direction)
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y
			* sin(-rot_speed);
		player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y
			* cos(-rot_speed);
	}
	// Rotation vers la droite (Flèche droite)
	// Applique une matrice de rotation 2D dans le sens horaire
	if (player->right_rotate)
	{
		// Rotation du vecteur de direction
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y
			* sin(rot_speed);
		player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y
			* cos(rot_speed);
		// Rotation du plan de caméra
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y
			* sin(rot_speed);
		player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y
			* cos(rot_speed);
	}
}
