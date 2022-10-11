# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 22:11:09 by sciftci           #+#    #+#              #
#    Updated: 2022/10/11 05:06:35 by sciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address
RM = rm -f

NAME = push_swap
NAME_CHECKER = checker

SRCS = 	push_swap.c input_check.c index.c sort.c stack.c fill_order.c cost_move.c instructions.c utils.c
BSRC =  checker.c fill_order.c instructions.c stack.c utils.c input_check.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRC:.c=.o)

all: ${NAME}

bonus: ${NAME} ${NAME_CHECKER}

${NAME}: $(OBJS)
	${CC} ${CFLAGS} -o $@ $(OBJS) 

${NAME_CHECKER}: $(BOBJS) libft
	${CC} ${CFLAGS} -o $@ $(BOBJS) -Llibft -lft

libft:
	make -C libft bonus

clean:
	$(RM) $(OBJS) $(BOBJS)
	make -C libft clean

fclean: clean
	$(RM) ${NAME} ${NAME_CHECKER} libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re