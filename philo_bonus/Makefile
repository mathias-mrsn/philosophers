NAME =		philo_bonus

SRCS = 		srcs/main.c \
			srcs/parsing.c


OBJS = ${SRCS:.c=.o}

INCS	=	-I ./includes

CC		=	clang

CFLAGS	=	

RM		=	rm -rf


.c.o:
			${CC} ${CFLAGS} ${INCS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${INCS} -lpthread ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
