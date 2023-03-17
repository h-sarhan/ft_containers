# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 00:48:08 by hsarhan           #+#    #+#              #
#    Updated: 2023/03/17 13:07:55 by hsarhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++

CXXFLAGS = -Wpedantic -Wall -Wextra -Werror -std=c++98 -g3 -Iutils -Icontainers # -fsanitize=address

NAME = tests

SRC = map_tests.cpp vector_tests.cpp main.cpp

OBJ := $(SRC:%.cpp=%.o)

all: $(NAME)
	sed -e '1s/^/[\'$$'\n''/' -e '$$s/,$$/\'$$'\n'']/' *.o.json > compile_commands.json
	rm -rf *.o.json

%.o: %.cpp
	$(CXX) -MJ $@.json $(CXXFLAGS) -c $^ 

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean