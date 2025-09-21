# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlarbi-a <wlarbi-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 16:25:27 by wlarbi-a          #+#    #+#              #
#    Updated: 2025/09/14 19:20:08 by wlarbi-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCE = ../getnextline/get_next_line_utils.c ../getnextline/get_next_line.c ./parsing/map_error.c ./parsing/utils.c ./parsing/utils2.c ./parsing/map_error2.c ./parsing/map_error3.c ./parsing/texture.c ./parsing/texture_error.c ./parsing/texture_error2.c ./parsing/texture_error3.c\
		 ./raycasting/draw.c ./raycasting/raycasting.c ./raycasting/player.c ./raycasting/main.c ./raycasting/init_game.c ./raycasting/find_player_start.c ./raycasting/draw_ray.c \
		  ./raycasting/config.c ./raycasting/cleanup.c ./raycasting/graphic.c ./raycasting/render.c raycasting/key.c
OBJ = ${SOURCE:.c=.o}
CC = cc
NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I../getnextline -I../minilibx-linux -I. -c $< -o $@

$(NAME): $(OBJ)
	@make -C ../libft --no-print-directory
	@make -C ../minilibx-linux --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) ../minilibx-linux/libmlx_Linux.a -I../minilibx-linux -lXext -lX11 -lm -o $(NAME) ../libft/libft.a
	@echo cub3d compiled

clean:
	@make -C ../libft clean --no-print-directory
	@make -C ../minilibx-linux clean --no-print-directory
	@rm -f $(OBJ)
	@echo cub3d objects deleted

fclean: clean
	@make -C ../libft fclean --no-print-directory
	@make -C ../minilibx-linux clean --no-print-directory
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
