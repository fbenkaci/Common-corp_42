/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:12:27 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/03/08 14:37:05 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <X11/Xlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	char			**grid;
	char			**cpy_grid;
	int				start;
	int				exit;
	unsigned int	item;
	void			*img;
	int				line_length;
	int				img_width;
	int				img_height;
	void			*background;
	void			*win;
	void			*mlx;
	int				player_x;
	int				player_y;
	int				moves;
	int				total_cols;
	int				total_rows;
	void			*eexit;
	void			*iitem;
	void			*wall;
	void			*perso;
	char			*str;
	int				nb_moves;
}					t_data;

void				print_map(t_data *map);
int					keypress(int keycode, t_data *data);
int					close_window(t_data *data);
char				*gnl(char *str);
void				free_map(char **grid);
int					check_map_borders(t_data *map);
int					check_map_rectangle(t_data *map);
int					check_map_objects(t_data *map);
int					check_valid_path(t_data *map);
int					load_map(t_data *map);
int					verif_filename(char *str);
void				coordonne_player(t_data *img);
void				move_player(int keycode, t_data *img);
void				move_up(int keycode, t_data *img);
void				move_down(int keycode, t_data *img);
void				move_right(int keycode, t_data *img);
void				move_left(int keycode, t_data *img);
void				free_images(t_data *img);
void				img_mlx_null(t_data img);
int					init_grid(t_data *img, char **av);
void				run_game(t_data *img);
void				kill(int keycode, t_data *img);
void				new_win(t_data img);
void				stop_count_w(t_data *img);
void				stop_count_s(t_data *img);
void				stop_count_a(t_data *img);
void				stop_count_d(t_data *img);
void				mlx_error(t_data img);

# define W 119
# define S 115
# define D 100
# define A 97
# define WIDTH 32
# define HEIGHT 32
#endif