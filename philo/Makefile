# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/11 03:02:00 by cyuuki            #+#    #+#              #
#    Updated: 2021/07/15 16:15:51 by cyuuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
DIR			=	./srcs
HEADER		=	./header
FILES		=	philo.c init_value.c parse_value.c utils.c work.c
HEADER_F	=	philo.h

SRCS		=	$(addprefix $(DIR)/, $(FILES))
HEADER_COMP	=	$(addprefix $(HEADER)/, $(HEADER_F))
INCLUDES	=	-I$(HEADER)
OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
FLAGS		=	-g -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)

%.o: %.c $(HEADER_COMP)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re