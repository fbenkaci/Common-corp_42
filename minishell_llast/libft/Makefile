NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_strlcpy.c  ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	   ft_memmove.c ft_strdup.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_atoll_safe.c ft_calloc.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	   ft_putnbr_fd.c ft_strcpy.c ft_strcmp.c ft_free_array.c

SRCSBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJSBONUS = $(SRCSBONUS:.c=.o)		

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) $(OBJSBONUS)
	ar rcs $@ $^

clean:
	rm -rf $(OBJS) $(OBJSBONUS)

fclean: clean
	rm -rf $(NAME) 

re: fclean all

bonus: $(OBJS) $(OBJSBONUS)
	ar rcs $(NAME) $(OBJS) $(OBJSBONUS)

.PHONY: all clean fclean re bonus