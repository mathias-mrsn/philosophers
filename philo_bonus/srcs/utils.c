/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:57 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/22 15:00:38 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t
	__get_time__(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	__is_dead__(t_global *ph)
{
	sem_post(ph->stop);
	sem_wait(ph->talk);
	usleep(1000);
	printf("[%8lu] %d \x1B[31m%s\x1B[0m\n",
		(__get_time__() - ph->start_time), ph->id_stock, DEAD);
	sem_post(ph->talk);
}

void
	__status__(int id, int status, t_global *ph)
{
	const char	*stat[5] = {DEAD, FORK, EAT, SLEEP, THINK};

	sem_wait(ph->talk);
	if (!ph->stop_value)
	{
		if (status == 0)
			printf("[%8lu] %d \x1B[31m%s\x1B[0m\n",
				(__get_time__() - ph->start_time), id + 1, stat[status]);
		else
			printf("[%8lu] %d %s\n",
				(__get_time__() - ph->start_time), id + 1, stat[status]);
		if (status == 0)
		{
			sem_post(ph->stop);
			ph->stop_value = 1;
			usleep(1000);
		}
	}
	sem_post(ph->talk);
}

int
	__still_alive__(t_philo	*philo, t_global *ph)
{
	if (__get_time__() - philo->last_meal <= (uint64_t)ph->time_to_die)
		return (SUCCESS);
	return (ERROR);
}

void
	__usleep__(size_t	time, t_global *ph)
{
	const size_t	instant_t = __get_time__();

	while (!ph->stop_value && __get_time__() - instant_t < time)
		usleep(500);
}
