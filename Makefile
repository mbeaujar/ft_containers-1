# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/19 17:22:16 by ranaili           #+#    #+#              #
#    Updated: 2021/10/04 16:07:36 by ranaili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = 	containers/map.hpp \
			containers/utils.hpp \
			containers/stack.hpp \
			containers/vector.hpp \
			containers/iterator.hpp

NAME = a.out

CC = clang++

SRCS =	main.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAG = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

%.o : %.cpp $(HEADER)
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJS) 
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)

comp: 
	@clang++ -D FT=1 main.cpp -Icontainers -o ft && ./ft > output_ft
	@clang++ main.cpp -o std && ./std > output_std
	@-diff output_ft output_std
	@-rm -rf output_std output_ft

clean :
	rm -f $(OBJS)
	@-rm -f output_ft
	@-rm -f output_std
	@-rm -f ft std

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re