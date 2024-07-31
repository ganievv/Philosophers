# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 18:28:31 by sganiev           #+#    #+#              #
#    Updated: 2024/07/31 16:37:45 by sganiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/utils_1.c src/launch_philos.c src/routine.c src/monitoring.c \
src/getters.c src/setters.c src/utils_2.c src/utils_3.c \

CC = gcc

CFLAGS = -g -pthread -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, $(NAME)