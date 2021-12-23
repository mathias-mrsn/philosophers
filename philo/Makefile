# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 17:17:00 by mamaurai          #+#    #+#              #
#    Updated: 2021/12/20 09:54:59 by mamaurai         ###   ########.fr        #
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
			@printf "%-15s ${_YELLOW}${_BOLD}$<${_END}...\n" "Compiling"
			@${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			@printf "%-15s ${_GREEN}${_BOLD}${NAME}${_END}...\n" "Compiling"
			@${CC} ${CFLAGS} -g3 ${INCS} -lpthread ${OBJS} -o ${NAME}
			@printf "\n${_GREEN}${_BOLD}Compilation done !${_END}\n"

clean:
			@printf "%-15s ${_RED}${_BOLD}binary files${_END}...\n" "Deleting"
			@${RM} ${OBJS}

fclean:		clean
			@printf "%-15s ${_RED}${_BOLD}${NAME}${_END}...\n" "Deleting"
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
