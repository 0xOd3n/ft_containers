
NAME = Container

FLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDE = 	containers/vector/vector.hpp \
			containers/vector/random_access_iterator.hpp \
			containers/stack/stack.hpp \
			containers/map/map.hpp \
			containers/map/AVL_Tree.hpp \
			containers/map/map_iterator.hpp \
			containers/map/pair.hpp \
			containers/iterator_traits.hpp \
			containers/enable_if.hpp \
			containers/is_integral.hpp \
			containers/reverse_iterator.hpp

SRCS = main.cpp

OBJ = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDE)
		c++ $(FLAGS) $(OBJ) -o $@

%.o : %.cpp $(INCLUDE)
		c++ $(FLAGS) -c $< -o $@

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : clean all

Phony : all clean fclean re