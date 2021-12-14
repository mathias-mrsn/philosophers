/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:54 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/14 17:16:55 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_philosopher_is_born(void	*content)
{
	t_global *ph = ((t_global *)content);
	int32_t	id;

	pthread_mutex_lock(&ph->lock);
	id = ph->set_id++;
	pthread_mutex_unlock(&ph->lock);
	ph->philosophers[id].last_meal = __get_time__();
	if (ph->philo_nbr == 1)
	{
		__status__(ph->philosophers[id].id, 1, ph);
		__usleep__(&ph->philosophers[id], (size_t)INT_MAX, ph);
		return (NULL);
	}
	while(SUCCESS == __still_alive__(&ph->philosophers[id], ph) && (!ph->times_must_eat || ph->philosophers[id].eaten_count < ph->times_must_eat))
	{
		ft_take_forks(&ph->philosophers[id], ph);
		ft_is_eating(&ph->philosophers[id], ph);
		ft_drop_forks(&ph->philosophers[id], ph);
		ft_is_sleeping(&ph->philosophers[id], ph);
		__status__(ph->philosophers[id].id, 4, ph);
		__usleep__(&ph->philosophers[id], (size_t)(ph->time_to_eat - ph->time_to_sleep), ph);
	}
	return (NULL);
}


void	ft_lets_go_eat(t_global	*ph)
{
	uint32_t i;

	i = 0;
	while(i < ph->philo_nbr)
	{
		pthread_mutex_init(&ph->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&ph->talk, NULL);
	pthread_mutex_init(&ph->lock, NULL);
	i = 0;
	pthread_mutex_lock(&ph->lock);
	while(i < ph->philo_nbr)
	{
		pthread_create(&ph->philosophers[i].philo, NULL, &ft_philosopher_is_born, ph);
		i++;
	}
	ph->start_time = __get_time_micro__();
	pthread_mutex_unlock(&ph->lock);
	i = 0;
	while(i < ph->philo_nbr)
		pthread_join(ph->philosophers[i++].philo, NULL);
}


