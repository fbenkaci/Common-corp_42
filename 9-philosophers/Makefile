NAME = philo
CC = cc -g3 -g -pthread -Wall -Wextra -Werror
SRCS = philosophers.c philosophers_utils_1.c philosophers_utils_2.c philosophers_utils_3.c philosophers_utils_4.c philosophers_utils_5.c philosophers_utils_6.c 
OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re