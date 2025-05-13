# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 11:15:59 by fbenkaci          #+#    #+#              #
#    Updated: 2025/05/13 08:19:06 by fbenkaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = util.c pipex.c path.c minishell.c
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