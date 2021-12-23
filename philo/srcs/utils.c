/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:56 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 22:03:03 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t
	__get_time__(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void
	__status__(int id, int status, t_global *ph)
{
	const char	*stat[5] = {DEAD, FORK, EAT, SLEEP, THINK};

	pthread_mutex_lock(&ph->talk);
	if (ph->stop_talking == 0)
	{
		if (status != 0)
			printf("[%8lu] %d %s\n",
				(__get_time__() - ph->start_time), id + 1, stat[status]);
		else
			printf("[%8lu] %d %s%s\033[0m\n",
				(__get_time__() - ph->start_time),
				id + 1, "\x1B[31m", stat[status]);
	}
	if (status == 0)
		ph->stop_talking = 1;
	pthread_mutex_unlock(&ph->talk);
}

int
	__still_alive__(t_philo	*philo, t_global *ph)
{	
	if ((uint64_t)__get_time__() - (uint64_t)
		philo->last_meal <= (uint64_t)ph->time_to_die)
		return (SUCCESS);
	__status__(philo->id, 0, ph);
	return (ERROR);
}

void
	__usleep__(size_t	time, t_global *ph)
{
	const size_t	instant_t = __get_time__();

	while (ph->stop == 0 && __get_time__() - instant_t < time)
		usleep(500);
}
