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

void	*alloc(t_global *ph);
void	quit(t_global *ph);
size_t	__get_time__(void);
void	__status__(int id, int status, t_global *ph);
int		__still_alive__(t_philo	*philo, t_global *ph);
void	__usleep__(size_t	time);
void	close_pid(t_global *ph);
void	close_semaphore(t_global *ph);
void	unlink_semaphore(void);
void	open_semaphore(t_global *ph);
void	ft_is_eating(t_philo *philo, t_global *ph);
void	ft_is_sleeping(t_philo *philo, t_global *ph);
void	ft_take_forks(t_philo *philo, t_global *ph);
void	ft_drop_forks(t_global *ph);
void	ft_start_meal(t_global *ph);

# endif
