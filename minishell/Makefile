# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 11:15:59 by fbenkaci          #+#    #+#              #
#    Updated: 2025/05/12 19:03:19 by fbenkaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = util.c pipex.c path.c
# main.c path.c handle_pipex.c handle_heredoc.c check_files.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  ft_printf/libftprintf.a  get_next_line/get_next_line.c libft/libft.a -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re