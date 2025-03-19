/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:20:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/09 12:29:59 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_img2(t_data *img)
{
	img->background = mlx_xpm_file_to_image(img->mlx,
			"textures/background.xpm", &img->img_width, &img->img_height);
	if (!img->background)
	{
		mlx_destroy_image(img->mlx, img->wall);
		mlx_destroy_image(img->mlx, img->iitem);
		mlx_destroy_image(img->mlx, img->perso);
		return (0);
	}
	img->eexit = mlx_xpm_file_to_image(img->mlx, "textures/exit.xpm",
			&img->img_width, &img->img_height);
	if (!img->eexit)
	{
		mlx_destroy_image(img->mlx, img->wall);
		mlx_destroy_image(img->mlx, img->iitem);
		mlx_destroy_image(img->mlx, img->perso);
		mlx_destroy_image(img->mlx, img->background);
		return (0);
	}
	return (1);
}

int	init_img(t_data *img)
{
	img->wall = mlx_xpm_file_to_image(img->mlx, "textures/wall.xpm",
			&img->img_width, &img->img_height);
	if (!img->wall)
		return (0);
	img->iitem = mlx_xpm_file_to_image(img->mlx, "textures/item.xpm",
			&img->img_width, &img->img_height);
	if (!img->iitem)
	{
		mlx_destroy_image(img->mlx, img->wall);
		return (0);
	}
	img->perso = mlx_xpm_file_to_image(img->mlx, "textures/perso.xpm",
			&img->img_width, &img->img_height);
	if (!img->perso)
	{
		mlx_destroy_image(img->mlx, img->wall);
		mlx_destroy_image(img->mlx, img->iitem);
		return (0);
	}
	if (init_img2(img) == 0)
		return (0);
	return (1);
}

void	fill_map(t_data *img, int y, int x)
{
	while (img->grid[y] != NULL)
	{
		x = 0;
		while (img->grid[y][x])
		{
			if (img->grid[y][x] == '1')
				mlx_put_image_to_window(img->mlx, img->win, img->wall, x
					* WIDTH, y * HEIGHT);
			else if (img->grid[y][x] == '0')
				mlx_put_image_to_window(img->mlx, img->win, img->background, x
					* WIDTH, y * HEIGHT);
			else if (img->grid[y][x] == 'P')
				mlx_put_image_to_window(img->mlx, img->win, img->perso, x
					* WIDTH, y * HEIGHT);
			else if (img->grid[y][x] == 'E')
				mlx_put_image_to_window(img->mlx, img->win, img->eexit, x
					* WIDTH, y * HEIGHT);
			else if (img->grid[y][x] == 'C')
				mlx_put_image_to_window(img->mlx, img->win, img->iitem, x
					* WIDTH, y * HEIGHT);
			x++;
		}
		y++;
	}
}

int	set_object(t_data *img)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (!img->grid)
	{
		ft_printf("Error.\nmap ou img->grid est NULL.\n");
		return (1);
	}
	if (init_img(img) == 0)
	{
		ft_printf("Error.\nL'initialisation des images a échoué.\n");
		free_map(img->grid);
		free_map(img->cpy_grid);
		mlx_destroy_window(img->mlx, img->win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);
		return (1);
	}
	fill_map(img, y, x);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	img;

	if (ac == 2)
	{
		if (verif_filename(av[1]) == 1)
			return (0);
		if (init_grid(&img, av) == 1)
			return (0);
		if (load_map(&img) == 1)
			return (0);
		img.mlx = mlx_init();
		if (!img.mlx)
		{
			mlx_error(img);
			return (0);
		}
		img.win = mlx_new_window(img.mlx, img.total_cols * 32, img.total_rows
				* 32, "so_long!");
		if (set_object(&img) == 1)
			return (0);
		run_game(&img);
	}
	ft_printf("Error.\nVous devez entrer un fichier\n");
	return (0);
}
