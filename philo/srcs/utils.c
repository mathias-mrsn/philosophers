/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:56 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/18 19:21:34 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	__get_time__(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	__status__(int id, int status, t_global *ph)
{
	const char	*stat[5] = {DEAD, FORK, EAT, SLEEP, THINK};
	const char	*colors[5] = {"\x1B[31m", "\x1B[33m",
		"\x1B[32m", "\x1B[36m", "\x1B[35m"};

	pthread_mutex_lock(&ph->talk);
	printf("[%8lu] %d %s%s\033[0m\n",
		(__get_time__() - ph->start_time), id, colors[status], stat[status]);
	if (status != 0)
		pthread_mutex_unlock(&ph->talk);
}

int	__still_alive__(t_philo	*philo, t_global *ph)
{	
	if ((uint64_t)__get_time__() - (uint64_t)
		philo->last_meal <= (uint64_t)ph->time_to_die)
		return (SUCCESS);
	__status__(philo->id, 0, ph);
	return (ERROR);
}

void	__usleep__(size_t	time)
{
	const size_t	instant_t = __get_time__();

	while (__get_time__() - instant_t < time)
		usleep(500);
}
