SOURCE =parsing/minishell.c  parsing/utils.c  parsing/parsing.c  parsing/parsing_pipe.c  parsing/parsing_redir.c parsing/fusion_token.c parsing/utils3.c \
		parsing/parsing_quote.c  parsing/path.c  parsing/utils2.c  parsing/special_tokens.c  parsing/handle.c  parsing/word_quote.c parsing/signal.c\
		builtins/builtins.c  builtins/cd.c builtins/cd_path.c builtins/env.c builtins/exit.c builtins/pwd.c builtins/export_utils.c builtins/unset.c builtins/echo.c builtins/export.c \
		execution/exec_utils.c execution/exec_utils_1.c execution/exec_utils_2.c execution/exec_utils_3.c execution/minishell_exec.c \
		execution/token_to_cmd_1.c execution/token_to_cmd_2.c execution/expand.c execution/expand_utils.c \
		heredoc/heredoc.c heredoc/heredoc_utils.c \

OBJ = ${SOURCE:.c=.o}
CC = cc
NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror 

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline libft/ft_printf/libftprintf.a  libft/libft.a

clean:
	@rm -f $(OBJ)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re