/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:17:43 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/23 09:07:14 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define INT32MAX_SIZE 11

# define SUCCESS 0
# define ERROR 1

# define EAT "is eating"
# define FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DEAD "died"

# define INVALID (-1)

# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include "philo_bonus_struct.h"

/*
    UTILS
*/

size_t	__get_time__(void);
void	__status__(int id, int status, t_global *ph);
int		__still_alive__(t_philo	*philo, t_global *ph);
void	__usleep__(size_t	time, t_global *ph);

/*
    MEMORY
*/

void	*alloc(t_global *ph);
void	close_pid(t_global *ph);
int		close_semaphore(t_global *ph);
int		unlink_semaphore(void);
void	open_semaphore(t_global *ph);
void	ft_exit(char *arg, char *text, int end, t_global *ph);

/*
    PARSING
*/
void	ft_parsing(int ac, char **av, t_global *ph);

/*
    DAILY_STEPS
*/

void	ft_is_eating(t_philo *philo, t_global *ph);
void	ft_is_sleeping(t_philo *philo, t_global *ph);
void	ft_take_forks(t_philo *philo, t_global *ph);
void	ft_drop_forks(t_global *ph);
void	ft_start_meal(t_global *ph);
void	__is_alone__(t_global *ph);

/*
	FORKS
*/

void	start_philo(t_global *ph);
void	*everyone_full(void *content);

#endif
