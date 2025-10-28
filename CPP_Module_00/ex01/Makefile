NAME = PhoneBook
CXX = c++ -Wall -Wextra -Werror -std=c++98 -g3
SRCS = main.cpp PhoneBook.cpp Contact.cpp 
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) 

re: fclean all

.PHONY: all clean fclean re