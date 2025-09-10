NAME = cub3D
CC = cc -Wall -Wextra -Werror -g3
SRCS = src/main.c src/main2.c src/player.c
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C mlx
	make -C libft
	$(CC) $(SRCS) libft/libft.a -Lmlx -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: clean all

.PHONY: all clean fclean re