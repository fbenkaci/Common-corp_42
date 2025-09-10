/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:30:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/09 19:03:01 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	find_player_start(t_game *game);

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || x < 0 || y < 0)
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

char	**get_map(void)
{
	char		**map;
	int			i;
	const char	*map_data[] = {"111111111111111111111111",
			"100000000000000000000001", "100000000000000000111101",
			"100000000000000000000001", "100000000000000000100101",
			"100000200020000000000001", "100000000000000000111101",
			"100000200020000000000001", "100000000000000000000001",
			"100000000000000000000001", "100000000000000000000001",
			"100000000000W0000000001", "100000000000000000000001",
			"100000000000000000000001", "100000000000000000000001",
			"100000000000000000000001", "100000000000000000000001",
			"100111000000000000111001", "100111000000000000111001",
			"100101000000000000101001", "100101000000000000101001",
			"100111000000000000111001", "100111000000000000111001",
			"111111111111111111111111", NULL};

	map = (char **)malloc(sizeof(char *) * 25);
	if (!map)
		return (NULL);
	i = 0;
	while (map_data[i])
	{
		map[i] = ft_strdup(map_data[i]);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	int	width;
	int	height;

	// Initialisation de la MLX
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
	{
		printf("Erreur : allocation mémoire pour ray\n");
		cleanup(game);
		exit(1);
	}
	game->texture[0].img = mlx_xpm_file_to_image(game->mlx,
			"./includes/mur1.xpm", &width, &height);
	if (!game->texture[0].img)
	{
		printf("Erreur : impossible de charger la texture mur1.xpm\n");
		cleanup(game);
		exit(1);
	}
	game->texture[0].data = mlx_get_data_addr(game->texture[0].img,
			&game->texture[0].bpp, &game->texture[0].size_line,
			&game->texture[0].endian);
	game->texture[0].width = width;
	game->texture[0].height = height;
	game->texture[1].img = mlx_xpm_file_to_image(game->mlx,
			"./includes/mur2.xpm", &width, &height);
	if (!game->texture[1].img)
	{
		printf("Erreur : impossible de charger la texture mur2.xpm\n");
		cleanup(game);
		exit(1);
	}
	game->texture[1].data = mlx_get_data_addr(game->texture[1].img,
			&game->texture[1].bpp, &game->texture[1].size_line,
			&game->texture[1].endian);
	game->texture[1].width = width;
	game->texture[1].height = height;
	game->texture[2].img = mlx_xpm_file_to_image(game->mlx,
			"./includes/mur3.xpm", &width, &height);
	if (!game->texture[2].img)
	{
		printf("Erreur : impossible de charger la texture mur3.xpm\n");
		cleanup(game);
		exit(1);
	}
	game->texture[2].data = mlx_get_data_addr(game->texture[2].img,
			&game->texture[2].bpp, &game->texture[2].size_line,
			&game->texture[2].endian);
	game->texture[2].width = width;
	game->texture[2].height = height;
	game->texture[3].img = mlx_xpm_file_to_image(game->mlx,
			"./includes/mur4.xpm", &width, &height);
	if (!game->texture[3].img)
	{
		printf("Erreur : impossible de charger la texture mur4.xpm\n");
		cleanup(game);
		exit(1);
	}
	game->texture[3].data = mlx_get_data_addr(game->texture[3].img,
			&game->texture[3].bpp, &game->texture[3].size_line,
			&game->texture[3].endian);
	game->texture[3].width = width;
	game->texture[3].height = height;
	// Initialisation de la carte
	game->map = get_map();
	if (!game->map)
	{
		// Handle error
		cleanup(game);
		exit(1);
	}
	// Set up map structure
	game->map_info.data = game->map;
	game->map_info.height = 0;
	while (game->map[game->map_info.height])
		game->map_info.height++;
	game->map_info.width = ft_strlen(game->map[0]);
	// Initialisation du joueur
	init_player(&game->player);
	// Recherche de la position de départ du joueur
	find_player_start(game);
	// Initialisation des couleurs
	game->ceiling_color = CEILING_COLOR;
	game->floor_color = FLOOR_COLOR;
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	find_player_start(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = x * BLOCK + BLOCK / 2;
				game->player.y = y * BLOCK + BLOCK / 2;
				if (c == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0;
				}
				else if (c == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0;
				}
				else if (c == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = 0.66;
				}
				else if (c == 'W')
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = -0.66;
				}
				// Remplacer le caractère du joueur par un espace
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
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

/*
** Fonction principale de raycasting qui calcule la distance au mur
** pour un rayon donné et dessine la colonne correspondante
*/
void	draw_line(t_player *player, t_game *game, float ray_angle, int x)
{
	float	pos_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	float	delta_dist_x;

	// distance le long du rayon pour traverser une case en X
	t_ray ray; // Variable locale au lieu d'utiliser game->ray
	// Position du joueur
	float pos_x = player->x / BLOCK; // Convertir en coordonnées de grille
	pos_y = player->y / BLOCK;
	// Direction du rayon
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	// Case de la grille où on se trouve
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	// Stocker le rayon dans game pour que vertical_line puisse y accéder
	game->ray = &ray;
	// Distance que doit parcourir le rayon pour passer d'une ligne x à la suivante
	// ou d'une ligne y à la suivante
	if (ray_dir_x == 0)
		// le rayon est vertical il monte ou descend sans jamais se déplacer à gauche ou à droite. C'est pour cela que l'on met une valeur presque infini.
		delta_dist_x = 1e30;
	// distance le long du rayon pour traverser une case en X,
	// il ne la traversera jamais.
	else
		delta_dist_x = fabs(1 / ray_dir_x);
	// distance que le rayon doit parcourir pour traverser une ligne verticale de la grille (passer d’une colonne à la suivante).
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1 / ray_dir_y);
	// Distance du point courant à la prochaine ligne x ou y
	// Direction du pas (+1 ou -1)
	//     int hit = 0;      // Y a-t-il eu collision avec un mur ?
	//     int side;         // Côté touché : 0 si côté x, 1 si côté y
	int hit = 0; // Y a-t-il eu collision avec un mur ?
	int side;    // Côté touché : 0 si côté x, 1 si côté y
	// Calculer le sens du pas et la distance initiale
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}
	// Algorithme DDA : avancer jusqu'à toucher un mur
	while (hit == 0)
	{
		// Sauter à la prochaine case de la grille
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		// Vérifier si le rayon a touché un mur
		if (game->map[map_y][map_x] == '1')
		{
			hit = 1;
		}
	}
	// Calculer la distance perpendiculaire au plan de la caméra
	// (pour éviter l'effet fisheye)
	if (side == 0)
		perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;
	// Calculer la hauteur de la ligne à dessiner
	line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	// Calculer les points de début et fin de la ligne
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	// Stocker les valeurs du rayon dans la structure
	ray.dir_x = ray_dir_x;
	ray.dir_y = ray_dir_y;
	game->ray = &ray;
	// Calculer la position exacte où le mur a été touché
	if (side == 0)
		game->wall_x = player->y / BLOCK + perp_wall_dist * ray_dir_y;
	else
		game->wall_x = player->x / BLOCK + perp_wall_dist * ray_dir_x;
	game->wall_x -= floor(game->wall_x);
	// Calculer la coordonnée x de la texture
	game->tex_x = (int)(game->wall_x * TEX_WIDTH);
	if (side == 0 && ray_dir_x > 0)
		game->tex_x = TEX_WIDTH - game->tex_x - 1;
	if (side == 1 && ray_dir_y < 0)
		game->tex_x = TEX_WIDTH - game->tex_x - 1;
	// Dessiner la colonne verticale avec texture
	vertical_line(game, x, draw_start, draw_end, side);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		ray_angle;
	int			i;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	char		debug_title[100];

	// float fraction;
	i = 0;
	player = &game->player;
	move_player(player, game);
	clear_image(game);
	// Pour chaque pixel de l'écran
	while (i < WINDOW_WIDTH)
	{
		// Calcul de la position x sur le plan de la caméra
		camera_x = 2 * i / (double)WINDOW_WIDTH - 1;
		// Direction du rayon = direction du joueur+ plan de caméra *position x
		ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray_dir_y = player->dir_y + player->plane_y * camera_x;
		// Calcul de l'angle du rayon
		ray_angle = atan2(ray_dir_y, ray_dir_x);
		draw_line(player, game, ray_angle, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	// Afficher les informations de débogage dans le titre de la fenêtre
	// snprintf(debug_title, sizeof(debug_title), "Cub3D - Dir(% .2f,
	// % .2f) Plane(% .2f, % .2f) ", player->dir_x, player->dir_y,
	// player->plane_x, player->plane_y);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, debug_title);
	return (1);
}

/*
** Nettoie la mémoire avant de quitter
*/
void	cleanup(t_game *game)
{
	int	i;

	// Libération de la carte
	i = 0;
	if (game->ray)
		free(game->ray);
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
	free(game->map);
	// Destruction de l'image et de la fenêtre
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

int	close_window(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	// Quand tel événement arrive dans la fenêtre, appelle ma fonction
	mlx_hook(game.win, 2, 1 << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1 << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	// Gestion de la fermeture de la fenêtre
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
