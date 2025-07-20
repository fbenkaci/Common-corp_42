/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:56:11 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/12 09:54:47 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_data *img)
{
	if (!img || !img->mlx)
		return ;
	if (img->wall)
		mlx_destroy_image(img->mlx, img->wall);
	if (img->iitem)
		mlx_destroy_image(img->mlx, img->iitem);
	if (img->perso)
		mlx_destroy_image(img->mlx, img->perso);
	if (img->background)
		mlx_destroy_image(img->mlx, img->background);
	if (img->eexit)
		mlx_destroy_image(img->mlx, img->eexit);
	return ;
}

void	coordonne_player(t_data *img)
{
	int	y;
	int	x;

	y = 0;
	while (img->grid[y])
	{
		x = 0;
		while (img->grid[y][x] != '\0')
		{
			if (img->grid[y][x] == 'P')
			{
				img->player_x = x;
				img->player_y = y;
				break ;
			}
			x++;
		}
		if (img->grid[y][x] == 'P')
			break ;
		y++;
	}
}

int	close_window(t_data *img)
{
	free_images(img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
		mlx_destroy_display(img->mlx);
	free(img->mlx);
	free_map(img->grid);
	free_map(img->cpy_grid);
	exit(0);
	return (0);
}

int	keypress(int keycode, t_data *img)
{
	kill(keycode, img);
	if (keycode == W)
	{
		move_up(keycode, img);
		stop_count_w(img);
	}
	if (keycode == S)
	{
		move_down(keycode, img);
		stop_count_s(img);
	}
	if (keycode == A)
	{
		move_left(keycode, img);
		stop_count_a(img);
	}
	if (keycode == D)
	{
		move_right(keycode, img);
		stop_count_d(img);
	}
	return (0);
}

void	run_game(t_data *img)
{
	coordonne_player(img);
	img->nb_moves = 0;
	mlx_hook(img->win, DestroyNotify, StructureNotifyMask, &close_window, img);
	mlx_hook(img->win, KeyPress, KeyPressMask, &keypress, img);
	mlx_loop(img->mlx);
}
