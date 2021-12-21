/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:46 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/21 18:22:08 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_is_eating(t_philo *philo, t_global *ph)
{
	if (!ph->stop_value)
		__status__(philo->id, 2, ph);
	sem_wait(ph->lock);
	philo->last_meal = __get_time__();
	philo->eaten_count++;
	if (philo->eaten_count == ph->times_must_eat)
		philo->state = 2;
	sem_post(ph->lock);
	__usleep__(ph->time_to_eat, ph);
}

void
	ft_is_sleeping(t_philo *philo, t_global *ph)
{	
	if (!ph->stop_value)
		__status__(philo->id, 3, ph);
	__usleep__(ph->time_to_sleep, ph);
}

void
	ft_take_forks(t_philo *philo, t_global *ph)
{
	sem_wait(ph->forks);
	if (!ph->stop_value)
		__status__(philo->id, 1, ph);
	sem_wait(ph->forks);
	if (!ph->stop_value)
		__status__(philo->id, 1, ph);
}

void
	ft_drop_forks(t_global *ph)
{
	sem_post(ph->forks);
	sem_post(ph->forks);
}

void
	__is_alone__(t_global *ph)
{
	__status__(ph->stop_value, 1, ph);
	__usleep__(ph->time_to_die + 100, ph);
}
