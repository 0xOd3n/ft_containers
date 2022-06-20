
NAME = Container

FLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDE = 	containers/vector/vector.hpp \
			containers/stack/stack.hpp 

SRCS = main.cpp

OBJ = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		c++ $(FLAGS) $(OBJ) -o $@

%.o : %.cpp $(INCLUDE)
		c++ $(FLAGS) -c $< -o $@

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : clean all

Phony : all clean fclean re