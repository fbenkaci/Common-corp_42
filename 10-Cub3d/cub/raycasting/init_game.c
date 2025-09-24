/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:51:32 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/20 19:27:11 by wlarbi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_all_textures(t_game *game, char **texture_paths)
{
	int	width;
	int	height;
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
				texture_paths[i], &width, &height);
		if (!game->texture[i].img || width != height)
		{
			printf("Erreur : impossible de charger la texture %d\n", i);
			cleanup(game);
			exit(1);
		}
		game->texture[i].data = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bpp, &game->texture[i].size_line,
				&game->texture[i].endian);
		game->texture[i].width = width;
		game->texture[i].height = height;
		i++;
	}
}

void	load_textures_from_config(t_game *game, char **files2)
{
	char	*texture_paths[4];

	texture_paths[0] = get_texture_path_from_config(files2, "EA");
	texture_paths[1] = get_texture_path_from_config(files2, "WE");
	texture_paths[2] = get_texture_path_from_config(files2, "SO");
	texture_paths[3] = get_texture_path_from_config(files2, "NO");
	if (!texture_paths[0] || !texture_paths[1] || !texture_paths[2]
		|| !texture_paths[3])
	{
		printf("Erreur : chemins de textures manquants\n");
		cleanup(game);
		exit(1);
	}
	load_all_textures(game, texture_paths);
}

void	set_colors_and_render(t_game *game, char **files2)
{
	int	floor_color;
	int	ceiling_color;

	floor_color = get_color_from_file2(files2, 'F');
	ceiling_color = get_color_from_file2(files2, 'C');
	if (floor_color == -1 || ceiling_color == -1)
	{
		printf("Erreur : couleurs F ou C manquantes\n");
		cleanup(game);
		exit(1);
	}
	game->floor_color = floor_color;
	game->ceiling_color = ceiling_color;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static void	init_ray_struct(t_game *game)
{
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
	{
		printf("Erreur : allocation mémoire pour ray\n");
		cleanup(game);
		exit(1);
	}
	game->ray->pos_x = 0.0;
	game->ray->pos_y = 0.0;
	game->ray->dir_x = 0.0;
	game->ray->dir_y = 0.0;
	game->ray->side_dist_x = 0.0;
	game->ray->side_dist_y = 0.0;
	game->ray->delta_dist_x = 0.0;
	game->ray->delta_dist_y = 0.0;
	game->ray->perp_wall_dist = 0.0;
	game->ray->map_x = 0;
	game->ray->map_y = 0;
	game->ray->step_x = 0;
	game->ray->step_y = 0;
	game->ray->side = 0;
}

void	init_game(t_game *game, char **file2)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->data_img = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	init_ray_struct(game);
	game->texture_pixels = NULL;
	load_textures_from_config(game, file2);
	setup_map_and_player(game);
	set_colors_and_render(game, file2);
}
