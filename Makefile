# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 18:28:31 by sganiev           #+#    #+#              #
#    Updated: 2024/06/26 09:40:46 by sganiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c launch_philos.c routine.c monitoring.c

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