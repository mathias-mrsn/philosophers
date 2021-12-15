#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define INT32MAX_SIZE 11

# define SUCCESS 0
# define ERROR 1

# define EAT "is eating"
# define FORK "took left forks"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DEAD "is dead"

# define INVALID (-1)

# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> 
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <errno.h>
# include <limits.h>
# include "philo_bonus_struct.h"

void	ft_parsing(int ac, char **av, t_global *ph);

void	ft_exit(char *arg, char *text, int r_val, t_global *ph);

# endif
