
SOURCE = parsing/minishell.c  parsing/utils.c  parsing/parsing.c  parsing/parsing_pipe.c  parsing/parsing_redir.c \
parsing/parsing_quote.c  parsing/path.c  parsing/utils2.c  parsing/special_tokens.c  parsing/handle.c  parsing/word_quote.c parsing/fusion_token.c  parsing/utils3.c \
execution/exec_utils_1.c execution/exec_utils_2.c execution/minishell_exec.c  execution/token_to_cmd_1.c execution/token_to_cmd_2.c    builtins/builtins.c  builtins/cd.c builtins/cd_path.c builtins/env.c builtins/exit.c builtins/pwd.c builtins/export_utils.c builtins/unset.c builtins/echo.c builtins/export.c
#expand.c
OBJ = ${SOURCE:.c=.o}
CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror 


all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline ft_printf/libftprintf.a  get_next_line/get_next_line.c libft/libft.a

clean:
	@rm -f $(OBJ)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re