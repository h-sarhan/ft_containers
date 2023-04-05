# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 00:48:08 by hsarhan           #+#    #+#              #
#    Updated: 2023/04/05 07:49:46 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++

CXXFLAGS = -Wpedantic -Wall -Wextra -Werror --std=c++98 -g3 -Iutils -Icontainers -Igerard/include # -fsanitize=address

NAME = tests

SRC = map_tests.cpp vector_tests.cpp main.cpp

OBJ := $(SRC:%.cpp=%.o)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean