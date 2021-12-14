/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:47 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/14 17:16:48 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_is_eating(t_philo *philo, t_global *ph)
{
	__status__(philo->id, 2, ph);
	philo->last_meal = __get_time__();
	philo->eaten_count++;
	__usleep__(philo, ph->time_to_eat, ph);
}

void	ft_is_sleeping(t_philo *philo, t_global *ph)
{
	__status__(philo->id, 3, ph);
	__usleep__(philo, ph->time_to_sleep, ph);
}

void	ft_take_forks(t_philo *philo, t_global *ph)
{
	unsigned int left;
	unsigned int right;

	left = philo->id;
	right = (philo->id + 1) % ph->philo_nbr;
	if(0 == philo->id % 2)
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

void	ft_drop_forks(t_philo *philo, t_global *ph)
{
	unsigned int left;
	unsigned int right;

	left = philo->id;
	right = (philo->id + 1) % ph->philo_nbr;
	if(1 == philo->id % 2)
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