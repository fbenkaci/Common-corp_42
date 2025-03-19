/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 09:35:17 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/14 15:00:30 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exitt(t_data *img)
{
	if (img->grid[img->player_y][img->player_x] == 'E' && img->item == 0)
	{
		free_images(img);
		mlx_destroy_window(img->mlx, img->win);
		mlx_destroy_display(img->mlx);
		free_map(img->grid);
		free_map(img->cpy_grid);
		free(img->mlx);
		exit(0);
	}
	return (0);
}

void	move_up(int keycode, t_data *img)
{
	if (keycode == W && img->grid[img->player_y - 1][img->player_x] != '1')
	{
		if (img->grid[img->player_y - 1][img->player_x] == 'C')
		{
			img->item--;
			img->grid[img->player_y - 1][img->player_x] = '0';
		}
		if (img->grid[img->player_y - 1][img->player_x] == 'E'
			&& img->item != 0)
			return ;
		mlx_put_image_to_window(img->mlx, img->win, img->background,
			img->player_x * WIDTH, img->player_y * HEIGHT);
		mlx_put_image_to_window(img->mlx, img->win, img->perso, img->player_x
			* WIDTH, (img->player_y - 1) * HEIGHT);
		img->player_y--;
	}
	exitt(img);
}

void	move_down(int keycode, t_data *img)
{
	if (keycode == S && img->grid[img->player_y + 1][img->player_x] != '1')
	{
		if (img->grid[img->player_y + 1][img->player_x] == 'C')
		{
			img->item--;
			img->grid[img->player_y + 1][img->player_x] = '0';
		}
		if (img->grid[img->player_y + 1][img->player_x] == 'E'
			&& img->item != 0)
			return ;
		mlx_put_image_to_window(img->mlx, img->win, img->background,
			img->player_x * WIDTH, img->player_y * HEIGHT);
		mlx_put_image_to_window(img->mlx, img->win, img->perso, img->player_x
			* WIDTH, (img->player_y + 1) * HEIGHT);
		img->player_y++;
	}
	exitt(img);
}

void	move_left(int keycode, t_data *img)
{
	if (keycode == A && img->grid[img->player_y][img->player_x - 1] != '1')
	{
		if (img->grid[img->player_y][img->player_x - 1] == 'C')
		{
			img->item--;
			img->grid[img->player_y][img->player_x - 1] = '0';
		}
		if (img->grid[img->player_y][img->player_x - 1] == 'E'
			&& img->item != 0)
			return ;
		mlx_put_image_to_window(img->mlx, img->win, img->background,
			img->player_x * WIDTH, img->player_y * HEIGHT);
		mlx_put_image_to_window(img->mlx, img->win, img->perso, (img->player_x
				- 1) * WIDTH, img->player_y * HEIGHT);
		img->player_x--;
	}
	exitt(img);
}

void	move_right(int keycode, t_data *img)
{
	if (keycode == D && img->grid[img->player_y][img->player_x + 1] != '1')
	{
		if (img->grid[img->player_y][img->player_x + 1] == 'C')
		{
			img->item--;
			img->grid[img->player_y][img->player_x + 1] = '0';
		}
		if (img->grid[img->player_y][img->player_x + 1] == 'E'
			&& img->item != 0)
			return ;
		mlx_put_image_to_window(img->mlx, img->win, img->background,
			img->player_x * WIDTH, img->player_y * HEIGHT);
		mlx_put_image_to_window(img->mlx, img->win, img->perso, (img->player_x
				+ 1) * WIDTH, img->player_y * HEIGHT);
		img->player_x++;
	}
	exitt(img);
}
