/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:31:00 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/08/26 19:13:12 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64

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

extern bool		g_done;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	double		time;
	double		old_time;

	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;

	int			map_x;
	int			map_y;

	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	// Ces valeurs servent à avancer le rayon dans la grille de la map,
	// pour savoir où il va toucher un mur
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int side; // Quel partie du mur est toucher N,S,E,O

	//////////////////////////////
	float		x;
	float		y;
	float		angle;

	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;

	bool		left_rotate;
	bool		right_rotate;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	int			hit;
	int			line_height;
	char		**map;
	int			draw_start;
	int			draw_end;
	int			side;
}				t_game;

void			init_player(t_player *player);
int				key_press(int keycode, t_player *player);
int				key_release(int keycode, t_player *player);
void			move_player(t_player *player);
void			init_dda(t_game *game);
void			compute_ray_dir(t_game *game, int x);
void			raycasting_loop(t_game *game);
int				game_loop(t_game *game);
void			find_wall(t_game *game);

#endif