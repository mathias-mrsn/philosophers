/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:46 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/14 17:33:48 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INT32MAX_SIZE 11

# define SUCCESS 0
# define ERROR 1

# define EAT "is eating"
# define FORK "took left forks"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DEAD "is dead"

# define INVALID (-1)

# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h> //mutex and threads
# include "philosophers_struct.h"

/*
    DAILY STEPS
*/

void	ft_take_forks(t_philo *philo, t_global *ph);
void	ft_is_sleeping(t_philo *philo, t_global *ph);
void	ft_is_eating(t_philo *philo, t_global *ph);
void	ft_drop_forks(t_philo *philo, t_global *ph);

/*	
    PARSING
*/

void	ft_parsing(int ac, char **av, t_global *p);

/*
    EXIT
*/

void	ft_exit(char *arg, char *text, bool	end, t_global *ph);

/*
    ROUTINE
*/

void	ft_lets_go_eat(t_global	*ph);

/*
    UTILS
*/

size_t	__get_time_micro__(void);
size_t	__get_time__(void);
void	__status__(int id, int status, t_global *ph);
void	__usleep__(t_philo *philo, size_t	time, t_global *ph);
int		__still_alive__(t_philo	*philo, t_global *ph);

#endif