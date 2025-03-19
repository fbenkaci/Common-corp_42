/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:47:40 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/14 14:58:28 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	stop_count_w(t_data *img)
{
	if (img->grid[img->player_y - 1][img->player_x] != '1'
		&& img->grid[img->player_y - 1][img->player_x] != 'E')
		ft_printf("%d\n", ++img->nb_moves);
}

void	stop_count_s(t_data *img)
{
	if (img->grid[img->player_y + 1][img->player_x] != '1'
		&& img->grid[img->player_y + 1][img->player_x] != 'E')
		ft_printf("%d\n", ++img->nb_moves);
}

void	stop_count_a(t_data *img)
{
	if (img->grid[img->player_y][img->player_x - 1] != '1'
		&& img->grid[img->player_y][img->player_x - 1] != 'E')
		ft_printf("%d\n", ++img->nb_moves);
}

void	stop_count_d(t_data *img)
{
	if (img->grid[img->player_y][img->player_x + 1] != '1'
		&& img->grid[img->player_y][img->player_x + 1] != 'E')
		ft_printf("%d\r\n", ++img->nb_moves);
}

void	kill(int keycode, t_data *img)
{
	if (keycode == XK_Escape)
		close_window(img);
}
