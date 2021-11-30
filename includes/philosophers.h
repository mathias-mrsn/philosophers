#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INT32MAX_SIZE 11

# define SUCCESS 0
# define ERROR 1

# define IS_EATING "is eating"
# define FORK_LEFT "took left forks"
# define FORK_RIGHT "took right fork"
# define IS_THINKING "is thinking"
# define IS_SLEEPING "is sleeping"
# define IS_DEAD "is dead"
# define DROP_LEFT "drop left"
# define DROP_RIGHT "drop right"


# define INVALID (-1)

# include <libc.h> // Delete it !

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h> //mutex and threads
# include "philosophers_struct.h"

/*	STRUCT		*/

t_global	*s(void);

/*	PARSING		*/

void	ft_parsing(int ac, char **av, t_global *p);

/*	FREE		*/

void	ft_exit(char *arg, char *text, bool	end);


void	ft_lets_go_eat(t_global	*ph);


#endif