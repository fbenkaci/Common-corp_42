/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:20:15 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/11 19:26:55 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Cette fonction calcule la distance jusqu'au mur pour un seul rayon
** Paramètres:
** - ray: Structure contenant les informations du rayon (direction, position...)
** - map: La carte du niveau
** Retourne: La distance jusqu'au mur et les informations de collision
*/

void	calculate_ray(t_ray *ray, t_map *map)
{
	// Vérification des limites de la carte
	if (ray->map_x < 0 || ray->map_x >= map->width || ray->map_y < 0
		|| ray->map_y >= map->height)
		return ;
	// Calcul du pas et de la distance jusqu'au prochain x/y sur la grille
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

/*
** Algorithme DDA (Digital Differential Analysis) pour trouver l'intersection
** avec un mur. Cette fonction continue le calcul commencé dans calculate_ray.
*/
void	perform_dda(t_ray *ray, t_map *map)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Collision avec un mur
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Collision avec un mur horizontal
		}
		if (ray->map_x >= 0 && ray->map_x < map->width && ray->map_y >= 0
			&& ray->map_y < map->height
			&& map->data[ray->map_y][ray->map_x] == '1')
			break ;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->dir_y;
}

/*
** Cette fonction initialise les variables nécessaires pour le raycasting
** pour un seul rayon. Elle est appelée pour chaque colonne de l'écran.
*/
void	init_ray(t_ray *ray, t_player *player, double camera_x)
{
	// Position initiale = position du joueur
	ray->pos_x = player->x;
	ray->pos_y = player->y;
	// Direction du rayon =
	// direction du joueur + plan de caméra * position x sur l'écran
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	// Position sur la carte
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	// Calcul de la distance à parcourir pour un déplacement unitaire
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

/*
** Fonction principale de rendu qui lance un rayon pour chaque colonne de l'écran
** et dessine les murs en fonction de la distance calculée
*/
void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;
	int		line_height;
	int		draw_start;
	int		draw_end;

	x = 0;
	while (x < WINDOW_WIDTH) // Pour chaque colonne de l'écran
	{
		game->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		// Position sur le plan caméra (entre -1 et 1)
		init_ray(&ray, &game->player, game->camera_x);
		// Initialisation du rayon
		calculate_ray(&ray, &game->map_info);
		// Calcul des distances initiales et des pas
		perform_dda(&ray, &game->map_info);
		// Exécution de l'algorithme DDA
		line_height = (int)(WINDOW_HEIGHT / ray.perp_wall_dist);
		// Calcul de la hauteur de la ligne à dessiner
		draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		// Calcul du début et de la fin de la ligne verticale
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		vertical_line(game, x, draw_start, draw_end, ray.side);
		// Dessin de la ligne verticale
		x++;
	}
	// Mise à jour de l'affichage
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
