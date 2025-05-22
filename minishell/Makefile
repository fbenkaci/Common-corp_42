# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 11:15:59 by fbenkaci          #+#    #+#              #
#    Updated: 2025/05/22 16:54:42 by fbenkaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS =  builtins/builtins.c builtins/cd.c builtins/cd_path.c builtins/echo.c builtins/env.c builtins/export.c builtins/export_utils.c builtins/pwd.c builtins/unset.c builtins/exit.c
#util.c pipex.c path.c minishell.c
# main.c path.c handle_pipex.c handle_heredoc.c check_files.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  ft_printf/libftprintf.a  get_next_line/get_next_line.c libft/libft.a -o $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re