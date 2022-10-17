# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 22:11:09 by sciftci           #+#    #+#              #
#    Updated: 2022/10/17 20:07:28 by sciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = push_swap
NAME_CHECKER = checker
NAME_VIS = vis

SRCS = 	push_swap.c input_check.c index.c sort.c stack.c fill_order.c cost_move.c instructions.c utils.c
BSRCS = checker.c fill_order.c instructions.c stack.c utils.c input_check.c gnl/*bonus.c
VSRCS = vis.c stack.c input_check.c fill_order.c utils.c instructions.c gnl/*bonus.c

all: ${NAME}

bonus: ${NAME} ${NAME_CHECKER}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

${NAME_CHECKER}:
	${CC} ${CFLAGS} ${BSRCS} -o ${NAME_CHECKER}

vis: 
	${CC} ${CFLAGS} ${VSRCS} -o ${NAME_VIS}

clean:

fclean: clean
	$(RM) ${NAME} ${NAME_CHECKER} ${NAME_VIS}

re: fclean all

reb: fclean bonus

rev: fclean vis

.PHONY: all bonus vis clean fclean re reb rev