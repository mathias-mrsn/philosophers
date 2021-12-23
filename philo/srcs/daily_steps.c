/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:47 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/23 08:51:14 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void
	ft_is_eating(t_philo *philo, t_global *ph)
{
	if (philo->state == 2)
		return ;
	__status__(philo->id, 2, ph);
	pthread_mutex_lock(&philo->lock_philo);
	philo->last_meal = __get_time__();
	philo->eaten_count++;
	if (philo->eaten_count == ph->times_must_eat)
	{
		philo->state = 2;
		ph->philo_done++;
	}
	pthread_mutex_unlock(&philo->lock_philo);
	__usleep__(ph->time_to_eat, ph);
}

void
	ft_is_sleeping(t_philo *philo, t_global *ph)
{
	if (philo->state == 2)
		return ;
	__status__(philo->id, 3, ph);
	__usleep__(ph->time_to_sleep, ph);
}

void
	ft_take_forks(t_philo *philo, t_global *ph)
{
	uint32_t	left;
	uint32_t	right;

	left = philo->id;
	right = (philo->id + 1) % ph->philo_nbr;
	if (philo->state == 2)
		return ;
	if (0 == philo->id % 2)
	{
		pthread_mutex_lock(&ph->forks[left]);
		__status__(philo->id, 1, ph);
		pthread_mutex_lock(&ph->forks[right]);
		__status__(philo->id, 1, ph);
	}
	else
	{
		pthread_mutex_lock(&ph->forks[right]);
		__status__(philo->id, 1, ph);
		pthread_mutex_lock(&ph->forks[left]);
		__status__(philo->id, 1, ph);
	}
}

void
	ft_drop_forks(t_philo *philo, t_global *ph)
{
	uint32_t	left;
	uint32_t	right;

	left = philo->id;
	right = (philo->id + 1) % ph->philo_nbr;
	if (0 == philo->id % 2)
	{
		pthread_mutex_unlock(&ph->forks[right]);
		pthread_mutex_unlock(&ph->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&ph->forks[left]);
		pthread_mutex_unlock(&ph->forks[right]);
	}
}
