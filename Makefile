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

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re