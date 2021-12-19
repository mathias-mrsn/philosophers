# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 17:17:00 by mamaurai          #+#    #+#              #
#    Updated: 2021/12/18 19:08:04 by mamaurai         ###   ########.fr        #
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
INCS	=	-I ./includes
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_REV=$'\x1b[7m

# Colors
_GREY=$'\x1b[30m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_CYAN=$'\x1b[36m
_WHITE=$'\x1b[37m

.c.o:
			@echo "Compiling ${_YELLOW}${_BOLD}$<${_END}..."
			@${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			@echo "Compiling ${_GREEN}${_BOLD}philo${_END}..."
			@${CC} ${CFLAGS} ${INCS} -lpthread ${OBJS} -o ${NAME}

clean:
			@echo "Deleting ${_RED}${_BOLD}binary files${_END}..."
			@${RM} ${OBJS}

fclean:		clean
			@echo "Deleting ${_RED}${_BOLD}philo${_END}..."
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
