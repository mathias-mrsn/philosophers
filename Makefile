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
