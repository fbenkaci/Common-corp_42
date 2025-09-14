/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:58:01 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/13 19:03:18 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data_img[index] = color & 0xFF;
	game->data_img[index + 1] = (color >> 8) & 0xFF;
	game->data_img[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
	y = WINDOW_HEIGHT / 2;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(x, y, 0xFF0000, game);
			x++;
		}
		y++;
	}
}

static void	draw_square(int x, int y, int size, t_game *game)
{
	int	i;
	int	color;

	i = 0;
	color = 0x0000FF;
	while (i < size)
		put_pixel(x + i++, y, color, game);
	i = 0;
	while (i < size)
		put_pixel(x, y + i++, color, game);
	i = 0;
	while (i < size)
		put_pixel(x + size, y + i++, color, game);
	i = 0;
	while (i < size)
		put_pixel(x + i++, y + size, color, game);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;

	y = 0;
	map = game->data.map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, game);
			x++;
		}
		y++;
	}
}
