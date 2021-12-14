/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:56 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/14 17:16:56 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	__get_time_micro__(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000000) + (time.tv_usec)));
}

size_t	__get_time__(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	__status__(int	id, int	status, t_global *ph)
{
	const char	*stat[5] = {DEAD, FORK, EAT, SLEEP, THINK};	
	pthread_mutex_lock(&ph->talk);
	printf("[%10lu] : philosopher %d, %s\n", (__get_time_micro__() - ph->start_time) / 1000, id, stat[status]);
	if (status != 0)
		pthread_mutex_unlock(&ph->talk);
}

int		__still_alive__(t_philo	*philo, t_global *ph)
{
	uint64_t	isdead;

	isdead = __get_time__() - philo->last_meal;
	if (isdead <= (uint64_t)ph->time_to_die)
		return (SUCCESS);
	__status__(philo->id, 0, ph);
	return (ERROR);
}

void	__usleep__(t_philo *philo, size_t	time, t_global *ph)
{
	const	size_t instant_t = __get_time__();

	while (SUCCESS == __still_alive__(philo, ph) && __get_time__() - instant_t < time)
		usleep(750);
}




