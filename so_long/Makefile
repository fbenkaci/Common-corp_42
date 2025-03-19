# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 12:41:19 by fbenkaci          #+#    #+#              #
#    Updated: 2025/03/09 12:28:26 by fbenkaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRCS = main.c valid_path.c load_map.c  check_map.c hooks.c move_player.c stop_count.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I../get_next_line -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	make -C ft_printf
	$(CC) $(OBJS) -L../mlx_linux -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME) libft/libft.a ft_printf/libftprintf.a

clean:
	make -C libft clean
	make -C ft_printf clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft fclean
	make -C ft_printf clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re