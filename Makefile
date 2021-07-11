# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/11 03:02:00 by cyuuki            #+#    #+#              #
#    Updated: 2021/07/11 03:22:42 by cyuuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
DIR			=	./srcs
HEADER		=	./includes
FILES		=	philo.c init_value.c parse_value.c utils.c work.c
HEADER_F	=	philo.h

SRCS		=	$(addprefix $(DIR)/, $(FILES))
HEADER_COMP	=	$(addprefix $(HEADER/, $(HEADER_F)))
INCLUDES	=	-I$(HEADER)
OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)

%.o: %.c $(HEADER_COMP)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(NAME)

re:
	fclean all

.PHONY all fclean re clean