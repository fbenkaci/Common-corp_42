/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:30:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/08/31 16:57:37 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	g_done = false;

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
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
	int		color;
	int		y;
	int		x;

	y = 0;
	map = game->map;
	color = 0x0000FF;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0xFF0000, game);
			x++;
		}
		y++;
	}
}

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 26);
	map[0] = "11111111111111111111111";
	map[1] = "10000000000000000000001";
	map[2] = "10000000000000000000001";
	map[3] = "10000000000000000000001";
	map[4] = "10000001100000000000001";
	map[5] = "10000001100000000000001";
	map[6] = "10000000000000000000001";
	map[7] = "10000000000000000000001";
	map[8] = "10000000000000000000001";
	map[9] = "10000000000000000000001";
	map[10] = "10000000000000000000001";
	map[11] = "10000000000000000000001";
	map[12] = "10000000000000000000001";
	map[13] = "10000000000000000000001";
	map[14] = "10000000000000000000001";
	map[15] = "10000000000000000000001";
	map[16] = "10000000000000000000001";
	map[17] = "10000000000000000000001";
	map[18] = "10000000000000000000001";
	map[19] = "10000000000000000000001";
	map[20] = "10000000000000000000001";
	map[21] = "10000000000000000000001";
	map[22] = "10000000000000000000001";
	map[23] = "10000000000000000000001";
	map[24] = "11111111111111111111111";
	map[25] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->hit = 0;
	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, 1280, 1024);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	(void)i;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}

void    draw_vertical_line(int x, int start, int end, int color, t_game *game)
{
    int y;

    y = start;
    while (y <= end)
    {
        put_pixel(x, y, color, game);
        y++;
    }
}

void    draw_walls(t_game *game, int x)
{
    int color;

    // Choix de la couleur du mur
    switch(game->map[game->player.map_y][game->player.map_x])
    {
        case '1':
            color = 0xFF0000;    // Rouge
            break;
        case '2':
            color = 0x00FF00;    // Vert
            break;
        case '3':
            color = 0x0000FF;    // Bleu
            break;
        case '4':
            color = 0xFFFFFF;    // Blanc
            break;
        default:
            color = 0xFFFF00;    // Jaune
            break;
    }

    // Assombrir les faces y (côtés) pour donner de la profondeur
    if (game->side == 1)
    {
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        r = r / 2;
        g = g / 2;
        b = b / 2;
        color = (r << 16) | (g << 8) | b;
    }

    // Dessiner la ligne verticale
    draw_vertical_line(x, game->draw_start, game->draw_end, color, game);
}

// int	draw_loop(t_game *game)
// {
// 	t_player	*player;
// 	float		fraction;
// 	float		start_x;
// 	int			i;

// 	// float		ray_x;
// 	// float		ray_y;
// 	// float		cos_angle;
// 	// float		sin_angle;
// 	i = 0;
// 	player = &game->player;
// 	move_player(player);
// 	clear_image(game);

// 	// Boucle de raycasting
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		compute_ray_dir(game, x);
// 		init_dda(game);
// 		find_wall(game);
		
// 		if (game->player.side == 0)
// 			game->player.perp_wall_dist = (game->player.side_dist_x - game->player.delta_dist_x);
// 		else
// 			game->player.perp_wall_dist = (game->player.side_dist_y - game->player.delta_dist_y);
		
// 		// Calculer la hauteur de la ligne à dessiner
// 		game->line_height = (int)(HEIGHT / game->player.perp_wall_dist);
// 		game->draw_start = -game->line_height / 2 + HEIGHT / 2;
// 		if (game->draw_start < 0)
// 			game->draw_start = 0;
// 		game->draw_end = game->line_height / 2 + HEIGHT / 2;
// 		if (game->draw_end >= HEIGHT)
// 			game->draw_end = HEIGHT - 1;
		
// 		// Dessiner le mur
// 		draw_walls(game, x);
// 		x++;
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return (1);
// }

bool	done(void)
{
	return (g_done);
}

void	compute_ray_dir(t_game *game, int x)
{
	game->player.camera_x = 2 * x / (double)WIDTH - 1;
	game->player.ray_dir_x = game->player.dir_x + game->player.plane_x
		* game->player.camera_x;
	game->player.ray_dir_y = game->player.dir_y + game->player.plane_y
		* game->player.camera_x;
	game->player.map_x = (int)game->player.pos_x;
	game->player.map_y = (int)game->player.pos_y;
	if (game->player.ray_dir_x == 0)
		game->player.delta_dist_x = 1e30;
	else
		game->player.delta_dist_x = fabs(1 / game->player.ray_dir_x);
	if (game->player.ray_dir_y == 0)
		game->player.delta_dist_y = 1e30;
	else
		game->player.delta_dist_y = fabs(1 / game->player.ray_dir_y);
	game->hit = 0; // est ce qu'un mur est touche ?
}

void	raycasting_loop(t_game *game)
{
	int	x;

	// int	side;

	while (!done())
	{
		x = 0;
		while (x < WIDTH)
		{
			compute_ray_dir(game, x);
			init_dda(game);
			find_wall(game);
			if (game->player.side == 0)
				game->player.perp_wall_dist = (game->player.side_dist_x - game->player.delta_dist_x);
			else
				game->player.perp_wall_dist = (game->player.side_dist_y - game->player.delta_dist_y);
			game->line_height = (int)(HEIGHT / game->player.perp_wall_dist);
			game->draw_start = -game->line_height / 2 + HEIGHT / 2;
			if (game->draw_start < 0)
				game->draw_start = 0;
			game->draw_end = game->line_height / 2 + HEIGHT / 2;
			if (game->draw_end >= HEIGHT)
				game->draw_end = HEIGHT - 1;
			draw_walls(game, x);
			x++;
		}
	}
}

void	init_dda(t_game *game)
{
	if (game->player.ray_dir_x < 0)
	{
		game->player.step_x = -1;
		game->player.side_dist_x = (game->player.pos_x - game->player.map_x)
			* game->player.delta_dist_x;
	}
	else
	{
		game->player.step_x = 1;
		game->player.side_dist_x = (game->player.map_x + 1.0
				- game->player.pos_x) * game->player.delta_dist_x;
	}
	if (game->player.ray_dir_y < 0)
	{
		game->player.step_y = -1;
		game->player.side_dist_y = (game->player.pos_y - game->player.map_y)
			* game->player.delta_dist_y;
	}
	else
	{
		game->player.step_y = 1;
		game->player.side_dist_y = (game->player.map_y + 1.0
				- game->player.pos_y) * game->player.delta_dist_y;
	}
}

void	find_wall(t_game *game)
{
	game->player.side = 0;
	while (game->hit == 0)
	{
		if (game->player.side_dist_x < game->player.side_dist_y)
		{
			game->player.side_dist_x += game->player.delta_dist_x;
			game->player.map_x += game->player.step_x;
			game->player.side = 0;
		}
		else
		{
			game->player.side_dist_y += game->player.delta_dist_y;
			game->player.map_y += game->player.step_y;
			game->player.side = 1;
		}
		if (game->player.map_y >= 0 && game->player.map_y < 24
			&& game->player.map_x >= 0 && game->player.map_x < 24)
		{
			if (game->map[game->player.map_y][game->player.map_x] == '1')
				game->hit = 1;
		}
	}
}

int	game_loop(t_game *game)
{
	// int	y;
	raycasting_loop(game);
	return (0);
}

int	close_window(void)
{
	g_done = true;
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	game_loop(&game);
	// mlx_hook(game.win, 2, 1 << 0, key_press, &game.player);
	// mlx_hook(game.win, 3, 1 << 1, key_release, &game.player);
	// mlx_loop_hook(game.mlx, draw_loop, &game);
	// mlx_hook(game.win, 17, 0, close_window, NULL);
	// 17 = événement fermeture fenêtre
	mlx_loop(game.mlx);
	return (0);
}
