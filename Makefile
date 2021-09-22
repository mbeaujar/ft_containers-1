# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ranaili <ranaili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/19 17:22:16 by ranaili           #+#    #+#              #
#    Updated: 2021/09/19 17:24:35 by ranaili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

CC = clang++

SRCS =	main.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAG = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

%.o : %.cpp
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re