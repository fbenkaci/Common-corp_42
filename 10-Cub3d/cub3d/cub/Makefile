# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 16:25:27 by wlarbi-a          #+#    #+#              #
#    Updated: 2025/09/11 18:45:36 by fbenkaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCE = ../getnextline/get_next_line_utils.c ../getnextline/get_next_line.c ./map_error.c ./utils.c ./main.c ./texture_error.c ./draw.c ./raycasting.c ./player.c ./main2.c
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
