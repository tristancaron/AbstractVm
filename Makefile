#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/18 14:57:12 by tcaron            #+#    #+#              #
#    Updated: 2015/01/18 14:57:12 by tcaron           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = avm

CFLAGS = -std=c++0x -Wall -Werror -Wextra

CC = g++

FILES = main.cpp \
		Core.cpp \
		Double.cpp \
		FactoryOperand.cpp \
		Float.cpp \
		Int8.cpp \
		Int16.cpp \
		Int32.cpp \
		Utils.cpp \
		MyException.cpp

SRC = $(addprefix lib/, $(FILES))

OBJ = $(SRC:lib/%.cpp=obj/%.o)

.PHONY: all clean fclean re dirobj

.SILENT: dirobj bindir

all: dirobj bindir $(NAME)

$(NAME): $(OBJ)
		$(CC) -o bin/$(NAME) $(OBJ) -Iinclude lib/libboost_regex.a

obj/%.o : lib/%.cpp
		$(CC) $(CFLAGS) -o $@ -c $^ -Iinclude

clean:
	rm -rf obj

fclean: clean
		rm -rf bin/$(NAME)

re: fclean all

dirobj:
	mkdir -p obj

bindir:
	mkdir -p bin