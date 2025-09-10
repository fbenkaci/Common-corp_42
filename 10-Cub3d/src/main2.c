// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main2.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/08/25 19:33:33 by fbenkaci          #+#    #+#             */
// /*   Updated: 2025/08/25 19:40:06 by fbenkaci         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "includes/cub3d.h"


// bool	done(void)
// {
// 	return (g_done);
// }

// void	compute_ray_dir(t_game *game, int x)
// {
// 	game->player.camera_x = 2 * x / (double)WIDTH - 1;
// 	game->player.ray_dir_x = game->player.dir_x + game->player.plane_x
// 		* game->player.camera_x;
// 	game->player.ray_dir_y = game->player.dir_y + game->player.plane_y
// 		* game->player.camera_x;
// 	game->player.map_x = (int)game->player.pos_x;
// 	game->player.map_y = (int)game->player.pos_y;
// 	if (game->player.ray_dir_x == 0)
// 		game->player.delta_dist_x = 1e30;
// 	else
// 		game->player.delta_dist_x = fabs(1 / game->player.ray_dir_x);
// 	if (game->player.ray_dir_y == 0)
// 		game->player.delta_dist_y = 1e30;
// 	else
// 		game->player.delta_dist_y = fabs(1 / game->player.ray_dir_y);
// 	game->hit = 0; // est ce qu'un mur est touche ?
// }

// void	raycasting_loop(t_game *game)
// {
// 	int	x;

// 	// int	side;

// 	while (!done())
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			compute_ray_dir(game, x);
// 			init_dda(game);
// 			find_wall(game);
// 			x++;
// 		}
// 	}
// }

// void	init_dda(t_game *game)
// {
// 	if (game->player.ray_dir_x < 0)
// 	{
// 		game->player.step_x = -1;
// 		game->player.side_dist_x = (game->player.pos_x - game->player.map_x)
// 			* game->player.delta_dist_x;
// 	}
// 	else
// 	{
// 		game->player.step_x = 1;
// 		game->player.side_dist_x = (game->player.map_x + 1.0
// 				- game->player.pos_x) * game->player.delta_dist_x;
// 	}
// 	if (game->player.ray_dir_y < 0)
// 	{
// 		game->player.step_y = -1;
// 		game->player.side_dist_y = (game->player.pos_y - game->player.map_y)
// 			* game->player.delta_dist_y;
// 	}
// 	else
// 	{
// 		game->player.step_y = 1;
// 		game->player.side_dist_y = (game->player.map_y + 1.0
// 				- game->player.pos_y) * game->player.delta_dist_y;
// 	}
// }

// void	find_wall(t_game *game)
// {
// 	game->side = 0;
// 	while (game->hit == 0)
// 	{
// 		if (game->player.side_dist_x < game->player.side_dist_y)
// 		{
// 			game->player.side_dist_x += game->player.delta_dist_x;
// 			game->player.map_x += game->player.step_x;
// 			game->side = 0;
// 		}
// 		else
// 		{
// 			game->player.side_dist_y += game->player.delta_dist_y;
// 			game->player.map_y += game->player.step_y;
// 			game->side = 1;
// 		}
// 		if (game->player.map_y >= 0 && game->player.map_y < 24
// 			&& game->player.map_x >= 0 && game->player.map_x < 24)
// 		{
// 			if (game->map[game->player.map_y][game->player.map_x] == '1')
// 				game->hit = 1;
// 		}
// 	}
// }

// int	game_loop(t_game *game)
// {
// 	// int	y;
// 	raycasting_loop(game);
// 	return (0);
// }

// int	main(void)
// {
// 	t_game	game;

// 	init_game(&game);
// 	game_loop(&game);

//     return (0);
// }
