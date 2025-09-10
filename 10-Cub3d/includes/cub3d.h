/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:28:35 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/09/09 16:52:25 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** typedef struct s_texture
{
	void	*img;		// Image MLX pour la texture
	char	*data;		// Données de l'image
	int		width;		// Largeur de la texture
	int		height;		// Hauteur de la texture
	int		bpp;		// Bits par pixel
	int		size_line;	// Taille d'une ligne
	int		endian;		// Endianness
}		t_texture;

typedef struct s_game
{
	void		*mlx;		// Pointeur MLX
	void		*win;		// Pointeur vers la fenêtre
	void		*img;		// Image MLX
	char		*data;		// Données de l'image
	int			bpp;		// Bits par pixel
	int			size_line;	// Taille d'une ligne
	int			endian;		// Endianness
	char		**map;		// Carte du niveau
	t_map		map_info;	// Structure d'information de la carte
	t_player	player;		// Données du joueur
	int			ceiling_color;	// Couleur du plafond
	int			floor_color;	// Couleur du sol
	t_texture	texture[4];	// Textures (N, S, E, W)
	double		wall_x;		// Position exacte où le mur a été touché
	int			tex_x;		// Coordonnée X de la texture
	int			tex_y;		// Coordonnée Y de la texture                                                                    */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:31:00 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/08/28 15:55:51 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define BLOCK 64
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define CEILING_COLOR 0x87CEEB // Bleu ciel
# define FLOOR_COLOR 0x808080  // GRIS 

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.14159265359

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ray
{
	double	pos_x;		// Position X du rayon
	double	pos_y;		// Position Y du rayon
	double	dir_x;		// Direction X du rayon
	double	dir_y;		// Direction Y du rayon
	double	side_dist_x;	// Distance au prochain côté vertical
	double	side_dist_y;	// Distance au prochain côté horizontal
	double	delta_dist_x;	// Distance entre deux intersections verticales
	double	delta_dist_y;	// Distance entre deux intersections horizontales
	double	perp_wall_dist;	// Distance perpendiculaire au mur
	int		map_x;		// Position X sur la carte
	int		map_y;		// Position Y sur la carte
	int		step_x;		// Direction du pas en X (-1 ou 1)
	int		step_y;		// Direction du pas en Y (-1 ou 1)
	int		side;		// Mur touché : vertical (0) ou horizontal (1)
}		t_ray;

typedef struct s_map
{
	char	**data;		// Tableau 2D contenant la carte
	int		width;		// Largeur de la carte
	int		height;		// Hauteur de la carte
}		t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}		t_player;

typedef struct s_texture
{
	void	*img;		// Image MLX pour la texture
	char	*data;		// Données de l'image
	int		width;		// Largeur de la texture
	int		height;		// Hauteur de la texture
	int		bpp;		// Bits par pixel
	int		size_line;	// Taille d'une ligne
	int		endian;		// Endianness
}		t_texture;

typedef struct s_game
{
	void		*mlx;		// Pointeur MLX
	void		*win;		// Pointeur vers la fenêtre
	void		*img;		// Image MLX
	char		*data;		// Données de l'image
	int			bpp;		// Bits par pixel
	int			size_line;	// Taille d'une ligne
	int			endian;		// Endianness
	char		**map;		// Carte du niveau
	t_map		map_info;	// Structure d'information de la carte
	t_player	player;		// Données du joueur
	int			floor_color;	// Couleur du sol
	int			ceiling_color;	// Couleur du plafond
	t_texture	texture[4];	// Textures (N, S, E, W)
	double		wall_x;		// Position exacte où le mur a été touché
	int			tex_x;		// Coordonnée X de la texture
	int			tex_y;		// Coordonnée Y de la texture
	t_ray		*ray;		// Rayon courant
}		t_game;

// Player functions
void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player, t_game *game);

// Raycasting functions
void	init_ray(t_ray *ray, t_player *player, double camera_x);
void	calculate_ray(t_ray *ray, t_map *map);
void	perform_dda(t_ray *ray, t_map *map);
void	render_frame(t_game *game);

// Drawing functions
void    put_pixel(int x, int y, int color, t_game *game);
void    draw_line(t_player *player, t_game *game, float ray_angle, int x);
void    vertical_line(t_game *game, int x, int start, int end, int side);
int		get_texture_color(t_texture *texture, int x, int y);
void	cleanup(t_game *game);


#endif