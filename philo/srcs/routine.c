/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:54 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 22:03:27 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	*ft_philosopher_is_born(void	*content)
{
	t_global	*ph;
	int32_t		id;

	ph = ((t_global *)content);
	pthread_mutex_lock(&ph->lock);
	id = ph->set_id++;
	ph->philosophers[id].last_meal = __get_time__();
	pthread_mutex_unlock(&ph->lock);
	if (0 == (id % 2) && ph->philo_nbr > 1)
		__usleep__(ph->time_to_eat, ph);
	while (!ph->stop && (-1 == ph->times_must_eat
			|| ph->philosophers[id].eaten_count < ph->times_must_eat))
	{
		ft_take_forks(&ph->philosophers[id], ph);
		ft_is_eating(&ph->philosophers[id], ph);
		ft_drop_forks(&ph->philosophers[id], ph);
		ft_is_sleeping(&ph->philosophers[id], ph);
		__status__(ph->philosophers[id].id, 4, ph);
		__usleep__((size_t)(ph->time_to_eat - ph->time_to_sleep), ph);
	}
	return (NULL);
}

static void
	*death(void	*content)
{
	t_global	*ph;
	uint32_t	i;
	int			test;

	i = 0;
	ph = ((t_global *)content);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&ph->philosophers[i].lock_philo);
		test = __still_alive__(&ph->philosophers[i], ph);
		pthread_mutex_unlock(&ph->philosophers[i].lock_philo);
		if (ph->philosophers[i].state != 2 && ERROR == test)
		{
			ph->stop = 1;
			return (NULL);
		}
		i++;
		if (i == ph->philo_nbr)
			i = 0;
	}
}

void
	ft_lets_go_eat(t_global	*ph)
{
	uint32_t	i;

	i = 0;
	while (i < ph->philo_nbr)
	{
		pthread_mutex_init(&ph->forks[i], NULL);
		pthread_mutex_init(&ph->philosophers[i].lock_philo, NULL);
		i++;
	}
	pthread_mutex_init(&ph->talk, NULL);
	pthread_mutex_init(&ph->lock, NULL);
	i = 0;
	pthread_mutex_lock(&ph->lock);
	while (i < ph->philo_nbr)
	{
		pthread_create(&ph->philosophers[i].philo,
			NULL, &ft_philosopher_is_born, ph);
		i++;
	}
	ph->start_time = __get_time__();
	pthread_mutex_unlock(&ph->lock);
	pthread_create(&ph->death, NULL, &death, ph);
	i = 0;
	while (i < ph->philo_nbr)
		pthread_join(ph->philosophers[i++].philo, NULL);
}
