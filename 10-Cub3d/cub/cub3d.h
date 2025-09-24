/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:27:43 by wlarbi-a          #+#    #+#             */
/*   Updated: 2025/09/24 15:09:04 by fbenkaci         ###   ########.fr       */
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
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265359

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
	double					pos_x;
	double					pos_y;
	double					dir_x;
	double					dir_y;
	double					side_dist_x;
	double					side_dist_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					perp_wall_dist;
	int						map_x;
	int						map_y;
	int						step_x;
	int						step_y;
	int						side;
	double					ray_dir_x;
	double					ray_dir_y;
}							t_ray;

typedef struct s_map
{
	char					**data;
	int						width;
	int						height;
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
	void					*img;
	char					*data;
	int						width;
	int						height;
	int						bpp;
	int						size_line;
	int						endian;
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
	void					*mlx;
	void					*win;
	void					*img;
	char					*data_img;
	int						bpp;
	int						size_line;
	int						endian;
	t_data					data;
	t_map					map_info;
	t_player				player;
	int						floor_color;
	int						ceiling_color;
	t_texture				texture[4];
	double					wall_x;
	int						tex_x;
	int						tex_y;
	int						close;
	double					camera_x;
	t_ray					*ray;
	int						**texture_pixels;
}							t_game;

typedef struct s_vline
{
	int						x;
	int						start;
	int						end;
	int						side;
}							t_vline;

/*Player functions*/
void						init_player(t_player *player);
int							key_press(int keycode, t_game *game);
int							key_release(int keycode, t_player *player);
void						move_player(t_player *player, t_game *game);
void						find_player_start(t_game *game);

/* Raycasting functions*/
void						init_game(t_game *game, char **file2);
char						*get_texture_path_from_config(char **file2,
								const char *prefix);
int							get_color_from_file2(char **file2, char identifier);
void						clear_image(t_game *game);
void						calculate_ray(t_ray *ray, t_map *map);
void						setup_map_and_player(t_game *game);
t_vline						prepare_vline(int x, t_raycast *r);
void						rotate_left(t_player *player, double rot_speed);
void						rotate_right(t_player *player, double rot_speed);
void						move_right(t_player *player, t_game *game,
								double speed);
void						move_left(t_player *player, t_game *game,
								double speed);

/* Drawing functions*/
int							draw_loop(t_game *game);
void						put_pixel(int x, int y, int color, t_game *game);
void						cast_single_ray(t_player *player, t_game *game,
								int x);
void						draw_vertical_line(t_game *game, t_vline vline);
int							get_texture_color(t_texture *texture, int x, int y);
void						cleanup(t_game *game);
int							close_window(t_game *game);
void						free_map(char **grid);
void						init_texture_pixels(t_game *game);
void						free_texture_pixels(t_game *game);
void						update_texture_pixels(t_game *game, t_raycast *ray,
								int x);

/* Parsing functions*/
char						*gnl_img(char *str);
int							ft_verif(t_data data);
int							flood_fill(t_data *data, int x, int y,
								char **copy_map);
int							validate_map_with_flood_fill(t_data *data);
int							get_map_height(char **map);
char						**copy_map(char **original_map);
void						coordinates(t_data *data, char **map);
void						map(t_data *data);
int							test_map(char **map);
int							validate_file_format(char *str);
int							verif_file_name(char *str);
int							is_map_line(char *str, int start);
int							is_empty_line_in_map(char *str, int pos);
char						get_first_non_space_char(char *line);
int							map_things(t_data *data);
int							map_count(t_data *data, char obj);
int							file_things(t_data *data);
int							check_texture_duplicates(t_data *data);
void						count_texture_identifiers(t_data *data,
								int *counts);
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
int							map_error_sides(char **map);
int							map_error(char **map);
int							verif_path(char **map);
int							check_bottom_line(char **map);
int							check_top_line(char **map);
void						free_split(char **split);
int							is_valid_rgb_value(char *str);
char						*trim_spaces(char *str);
int							is_texture_char(char c);
double						calculate_collision_distance(t_player *player,
								t_game *game, double dir_x, double dir_y);
int							verif_path2(char **map);
int							is_valid_texture_prefix(char first_char,
								char next_char);
#endif