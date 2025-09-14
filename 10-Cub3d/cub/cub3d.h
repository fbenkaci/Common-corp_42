/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:27:43 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/14 18:15:17 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../getnextline/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define BLOCK 64
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define CEILING_COLOR 0x87CEEB // Bleu ciel
# define FLOOR_COLOR 0x808080   // GRIS
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265359

// typedef struct s_player
// {
// 	int			x;
// 	int			y;
// }				t_player;

typedef struct s_game		t_game;
typedef struct s_raycast	t_raycast;

typedef struct s_raycast
{
	float					pos_x;
	float					pos_y;
	float					ray_dir_x;
	float					ray_dir_y;
	int						map_x;
	int						map_y;
	float					delta_dist_x;
	float					delta_dist_y;
	float					side_dist_x;
	float					side_dist_y;
	int						step_x;
	int						step_y;
	int						hit;
	int						side;
	float					perp_wall_dist;
	int						line_height;
	int						draw_start;
	int						draw_end;
}							t_raycast;

typedef struct s_ray
{
	double pos_x;          // Position X du rayon
	double pos_y;          // Position Y du rayon
	double dir_x;          // Direction X du rayon
	double dir_y;          // Direction Y du rayon
	double side_dist_x;    // Distance au prochain côté vertical
	double side_dist_y;    // Distance au prochain côté horizontal
	double delta_dist_x;   // Distance entre deux intersections verticales
	double delta_dist_y;   // Distance entre deux intersections horizontales
	double perp_wall_dist; // Distance perpendiculaire au mur
	int map_x;             // Position X sur la carte
	int map_y;             // Position Y sur la carte
	int step_x;            // Direction du pas en X (-1 ou 1)
	int step_y;            // Direction du pas en Y (-1 ou 1)
	int side;              // Mur touché : vertical (0) ou horizontal (1)
	double					ray_dir_x;
	double					ray_dir_y;
}							t_ray;

typedef struct s_map
{
	char **data; // Tableau 2D contenant la carte
	int width;   // Largeur de la carte
	int height;  // Hauteur de la carte
}							t_map;

typedef struct s_player
{
	float					x;
	float					y;
	float					angle;
	float					dir_x;
	float					dir_y;
	float					plane_x;
	float					plane_y;
	bool					key_up;
	bool					key_down;
	bool					key_left;
	bool					key_right;
	bool					left_rotate;
	bool					right_rotate;
}							t_player;

typedef struct s_texture
{
	void *img;     // Image MLX pour la texture
	char *data;    // Données de l'image
	int width;     // Largeur de la texture
	int height;    // Hauteur de la texture
	int bpp;       // Bits par pixel
	int size_line; // Taille d'une ligne
	int endian;    // Endianness
}							t_texture;

typedef struct s_data
{
	char					**map;
	char					**file2;
	char					**file;
	t_player				player;
}							t_data;

typedef struct s_game
{
	void *mlx;      // Pointeur MLX
	void *win;      // Pointeur vers la fenêtre
	void *img;      // Image MLX
	char *data_img; // Données de l'image
	int bpp;        // Bits par pixel
	int size_line;  // Taille d'une ligne
	int endian;     // Endianness
	t_data					data;
	t_map map_info;       // Structure d'information de la carte
	t_player player;      // Données du joueur
	int floor_color;      // Couleur du sol
	int ceiling_color;    // Couleur du plafond
	t_texture texture[4]; // Textures (N, S, E, W)
	double wall_x;        // Position exacte où le mur a été touché
	int tex_x;            // Coordonnée X de la texture
	int tex_y;            // Coordonnée Y de la texture
	int						close;
	double					camera_x;
	t_ray *ray; // Rayon courant
}							t_game;

typedef struct s_vline
{
	int						x;
	int						start;
	int						end;
	int						side;
}							t_vline;

// Player functions
void						init_player(t_player *player);
int							key_press(int keycode, t_game *game);
int							key_release(int keycode, t_player *player);
void						move_player(t_player *player, t_game *game);
void						find_player_start(t_game *game);

// Raycasting functions
void						init_game(t_game *game, char **file2);
char						*get_texture_path_from_config(char **file2,
								const char *prefix);
int							get_color_from_file2(char **file2, char identifier);
void						clear_image(t_game *game);
void						calculate_ray(t_ray *ray, t_map *map);
void						render_frame(t_game *game);
void						setup_map_and_player(t_game *game);
t_vline						prepare_vline(int x, t_raycast *r);

// Drawing functions
int							draw_loop(t_game *game);
void						put_pixel(int x, int y, int color, t_game *game);
void						draw_line(t_player *player, t_game *game,
								float ray_angle, int x);
void						draw_vertical_line(t_game *game, t_vline vline);
int							get_texture_color(t_texture *texture, int x, int y);
void						cleanup(t_game *game);
int							close_window(t_game *game);
void						free_map(char **grid);

// Parsing functions
char						*gnl_img(char *str);
int							ft_verif(t_data data);
int							flood_fill(t_data *data, int x, int y,
								char **copy_map);
void						coordinates(t_data *data, char **map);
void						map(t_data *data);
int							test_map(char **map);
int							validate_file_format(char *str);
int							is_map_line(char *str, int start);
int							is_empty_line_in_map(char *str, int pos);
char						get_first_non_space_char(char *line);
int							map_things(t_data *data);
int							map_count(t_data *data, char obj);
int							file_things(t_data *data);
char						*get_texture_path(char *line);
int							file_exists(char *path);
int							validate_texture_line(char *line);
int							get_first_non_space_index(char *line);
int							parse_color_line(char *line, int *r, int *g,
								int *b);
int							validate_color_line(char *line);
int							get_color_from_file2(char **file2, char identifier);
void						print_table_of_table(char **table);
void						free_char_tab(char **tab);
#endif