/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:30:23 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/11 19:06:52 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path_from_config(char **file2, const char *prefix)
{
	int	i;
	int	idx;

	i = 0;
	while (file2[i])
	{
		idx = 0;
		while (file2[i][idx] == ' ' || file2[i][idx] == '\t')
			idx++;
		if (ft_strncmp(&file2[i][idx], prefix, ft_strlen(prefix)) == 0)
		{
			idx += ft_strlen(prefix);
			while (file2[i][idx] == ' ' || file2[i][idx] == '\t')
				idx++;
			return (&file2[i][idx]);
		}
		i++;
	}
	return (NULL);
}

int	get_color_from_file2(char **file2, char identifier)
{
	int	i;
	int	idx;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (file2[i])
	{
		idx = get_first_non_space_index(file2[i]);
		if (file2[i][idx] == identifier)
		{
			if (parse_color_line(file2[i], &r, &g, &b))
				return ((r << 16) | (g << 8) | b);
		}
		i++;
	}
	return (-1);
}

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
	map = game->data.map;
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

void	init_game(t_game *game, char **file2)
{
	int		width;
	int		height;
	char	*texture_paths[4];
	int		floor_color;
	int		ceiling_color;

	// Initialisation de la MLX
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->data_img = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
	{
		printf("Erreur : allocation mémoire pour ray\n");
		cleanup(game);
		exit(1);
	}
	// Récupération des chemins des textures depuis file2
	texture_paths[0] = get_texture_path_from_config(file2, "NO");
	texture_paths[1] = get_texture_path_from_config(file2, "SO");
	texture_paths[2] = get_texture_path_from_config(file2, "WE");
	texture_paths[3] = get_texture_path_from_config(file2, "EA");
	// Vérification que tous les chemins ont été trouvés
	if (!texture_paths[0] || !texture_paths[1] || !texture_paths[2]
		|| !texture_paths[3])
	{
		printf("Erreur : chemins de textures manquants\n");
		cleanup(game);
		exit(1);
	}
	// Chargement des textures avec les chemins récupérés
	game->texture[0].img = mlx_xpm_file_to_image(game->mlx, texture_paths[0],
			&width, &height);
	if (!game->texture[0].img)
	{
		printf("Erreur : impossible de charger la texture NO\n");
		cleanup(game);
		exit(1);
	}
	game->texture[0].data = mlx_get_data_addr(game->texture[0].img,
			&game->texture[0].bpp, &game->texture[0].size_line,
			&game->texture[0].endian);
	game->texture[0].width = width;
	game->texture[0].height = height;
	// Chargement des autres textures
	for (int i = 1; i < 4; i++)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
				texture_paths[i], &width, &height);
		if (!game->texture[i].img)
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
	}
	// Initialisation de la carte
	// game->map = get_map();
	if (!game->data.map)
	{
		// Handle error
		cleanup(game);
		exit(1);
	}
	// Set up map structure
	game->map_info.data = game->data.map;
	game->map_info.height = 0;
	while (game->data.map[game->map_info.height])
		game->map_info.height++;
	game->map_info.width = ft_strlen(game->data.map[0]);
	// Initialisation du joueur
	init_player(&game->player);
	// Recherche de la position de départ du joueur
	find_player_start(game);
	// Récupération des couleurs depuis file2
	floor_color = get_color_from_file2(file2, 'F');
	ceiling_color = get_color_from_file2(file2, 'C');
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

void	find_player_start(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->data.map[y])
	{
		x = 0;
		while (game->data.map[y][x])
		{
			c = game->data.map[y][x];
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
				game->data.map[y][x] = '0';
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
	if (game->data.map[y][x] == '1')
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
	// Position du joueur
	float pos_x = player->x / BLOCK; // Convertir en coordonnées de grille
	pos_y = player->y / BLOCK;
	// Direction du rayon
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	// Case de la grille où on se trouve
	map_x = (int)pos_x;
	map_y = (int)pos_y;
	// Utiliser directement game->ray au lieu d'une variable locale
	game->ray->dir_x = ray_dir_x;
	game->ray->dir_y = ray_dir_y;
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
		if (map_y >= 0 && map_x >= 0 && 
			map_y < game->map_info.height && 
			map_x < (int)ft_strlen(game->data.map[map_y]) &&
			game->data.map[map_y][map_x] == '1')
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
	game->ray->dir_x = ray_dir_x;
	game->ray->dir_y = ray_dir_y;
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
	// char		debug_title[100];

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
	// mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, debug_title);
	return (1);
}


void	free_map(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != NULL)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

/*
** Nettoie la mémoire avant de quitter
*/
void	cleanup(t_game *game)
{
	int	i;

	// Libération de la mémoire
	if (game->ray)
		free(game->ray);
	// Libération de la carte si elle existe
	if  (game->data.file)
		free_map(game->data.file);
	if  (game->data.file2)
		free_map(game->data.file2);
	if (game->data.map)
	{
		i = 0;
		while (game->data.map[i])
		{
			free(game->data.map[i]);
			i++;
		}
		free(game->data.map);
	}
	// Destruction des textures
	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
	// Destruction de l'image et de la fenêtre
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	// exit(0);
}

int	close_window(t_game *game)
{
	if (game->close)
		return (0);
	game->close = 1;
	cleanup(game);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_data	data;
	char	*file_content;
	int		i;

	i = 0;
	// Initialisation complète de la structure game
	game.mlx = NULL;
	game.win = NULL;
	game.img = NULL;
	game.data_img = NULL;
	game.ray = NULL;
	game.data.map = NULL;
	game.data.file2 = NULL;
	game.data.file = NULL;
	game.close = 0;
	while (i < 4)
	{
		game.texture[i].img = NULL;
		i++;
	}
	// Initialisation de la structure data
	data.map = NULL;
	data.file2 = NULL;
	data.file = NULL;
	data.player.x = 0;
	data.player.y = 0;
	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	// Validation du format et lecture du fichier
	if (!validate_file_format(argv[1]))
	{
		printf("Erreur : format de fichier invalide\n");
		return (1);
	}
	// Lecture du fichier et séparation des sections
	file_content = gnl_img(argv[1]);
	if (!file_content)
	{
		printf("Erreur : impossible de lire le fichier\n");
		return (1);
	}
	data.file = ft_split(file_content, '\n');
	free(file_content);
	if (!data.file)
	{
		printf("Erreur : impossible de traiter le fichier\n");
		return (1);
	}
	// Séparation de la configuration et de la map
	map(&data);
	ft_verif(data);
	// Vérification que file2 a été initialisé
	if (!data.file2)
	{
		printf("Erreur : données de configuration manquantes\n");
		return (1);
	}
	// Copie des données dans la structure game
	game.data = data;
	init_game(&game, data.file2);
	// Quand tel événement arrive dans la fenêtre, appelle ma fonction
	mlx_hook(game.win, 2, 1 << 0, key_press, &game);
	mlx_hook(game.win, 3, 1 << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_window, &game);
	// Gestion de la fermeture de la fenêtre
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	
	return (0);
}
