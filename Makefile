# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 17:17:00 by mamaurai          #+#    #+#              #
#    Updated: 2021/12/14 17:17:00 by mamaurai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRCS = 		srcs/main.c \
			srcs/parsing.c \
			srcs/exit.c \
			srcs/routine.c \
			srcs/utils.c \
			srcs/daily_steps.c

OBJS = ${SRCS:.c=.o}

INCS	=	-I ./includes -I libft/includes/

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf


.c.o:
			${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -g3 -fsanitize=address ${INCS} -lpthread ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
