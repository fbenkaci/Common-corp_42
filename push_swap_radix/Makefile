# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 10:27:13 by fbenkaci          #+#    #+#              #
#    Updated: 2025/04/21 17:07:49 by fbenkaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
SRCS = parsing.c parsing_utils.c algo.c swap.c rotate.c push.c
OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a libft/ft_printf/libftprintf.a -o $(NAME)

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re