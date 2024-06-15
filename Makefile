# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 18:28:31 by sganiev           #+#    #+#              #
#    Updated: 2024/06/15 16:30:12 by sganiev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c ft_itoa.c

CFLAGS = -pthread -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(NAME)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, $(NAME)