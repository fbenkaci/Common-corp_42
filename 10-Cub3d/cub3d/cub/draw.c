/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:20:15 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/10 15:02:44 by wlarbi-a         ###   ########.fr       */
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
/*
** Dessine une ligne verticale à l'écran avec la couleur appropriée
** x: position horizontale de la ligne
** start: position verticale de début
** end: position verticale de fin
** side: indique si c'est un mur N/S (0) ou E/W (1) pour l'ombrage
*/
void	vertical_line(t_game *game, int x, int start, int end, int side)
{
	int		y;
	int		color;
	int		tex_num;
	double	step;
	double	tex_pos;

	// Sélectionner la texture en fonction du côté touché
	tex_num = 0;
	if (side == 0)
	{
		if (game->ray->dir_x > 0)
			tex_num = 0; // Texture Nord
		else
			tex_num = 1; // Texture Sud
	}
	else
	{
		if (game->ray->dir_y > 0)
			tex_num = 2; // Texture Est
		else
			tex_num = 3; // Texture Ouest
	}
	// Calculer le pas de texture et la position initiale
	step = 1.0 * TEX_HEIGHT / (end - start);
	tex_pos = (start - WINDOW_HEIGHT / 2 + (end - start) / 2) * step;
	y = 0;
	// Dessine le plafond
	while (y < start)
	{
		put_pixel(x, y, game->ceiling_color, game);
		y++;
	}
	// Dessine le mur texturé
	while (y < end)
	{
		game->tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		// Obtenir la couleur de la texture
		color = get_texture_color(&game->texture[tex_num], game->tex_x,
				game->tex_y);
		// Assombrir pour les murs N/S
		if (side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(x, y, color, game);
		y++;
	}
	// Dessine le sol
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(x, y, game->floor_color, game);
		y++;
	}
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	int		index;
	int		color;
	char	*ptr;

	// Vérifier les limites
	if (x >= texture->width || y >= texture->height || x < 0 || y < 0)
		return (0);
	// Calculer l'index dans les données de la texture
	index = y * texture->size_line + x * (texture->bpp / 8);
	ptr = texture->data + index;
	// Extraire la couleur (format BGRA ou RGBA selon l'endianness)
	color = *(int *)ptr;
	return (color);
}
