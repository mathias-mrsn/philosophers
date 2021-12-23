/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:53 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/23 09:25:11 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
	*death(void	*content)
{
	t_global	*ph;
	uint32_t	i;

	i = 0;
	ph = ((t_global *)content);
	__usleep__(ph->time_to_die, ph);
	while (0 == ph->stop_value)
	{
		usleep(100);
		if (ERROR == __still_alive__(&ph->philosophers[ph->id_stock], ph))
		{	
			if (!ph->stop_value)
				__status__(ph->id_stock, 0, ph);
			return (NULL);
		}
		i++;
		if (i == ph->philo_nbr)
			i = 0;
	}
	return (NULL);
}

static	void
	*stop_proc(void *content)
{
	t_global	*ph;

	ph = ((t_global *)content);
	sem_wait(ph->stop);
	ph->stop_value = 1;
	sem_post(ph->stop);
	return (NULL);
}

static void
	*ft_philosopher_is_born(t_global *ph, const uint32_t id)
{
	pthread_t	monitor;
	pthread_t	death_monitor;

	ph->philosophers[id].last_meal = __get_time__();
	if (pthread_create(&death_monitor, NULL, &death, ph)
		|| pthread_create(&monitor, NULL, &stop_proc, ph))
		return (NULL);
	if (0 == (id % 2) && ph->philo_nbr > 1)
		__usleep__(ph->time_to_eat, ph);
	if (1 == ph->philo_nbr)
		return (__is_alone__(ph), NULL);
	while (!ph->stop_value)
	{
		ft_take_forks(&ph->philosophers[id], ph);
		ft_is_eating(&ph->philosophers[id], ph);
		ft_drop_forks(ph);
		ft_is_sleeping(&ph->philosophers[id], ph);
		if (ph->stop_value != 1)
			__status__(ph->philosophers[id].id, 4, ph);
	}
	if (ph->philosophers[id].state != 2)
		sem_post(ph->sem_done);
	pthread_join(death_monitor, NULL);
	pthread_join(monitor, NULL);
	return (NULL);
}

void
	start_philo(t_global *ph)
{
	uint32_t	index;
	uint32_t	id;

	index = 0;
	id = 0;
	while (index < ph->philo_nbr)
	{
		ph->philosophers[index].id = id++;
		ph->philosophers[index].pid = fork();
		if (ph->philosophers[index].pid < 0)
			return ;
		else if (ph->philosophers[index].pid == 0)
		{
			open_semaphore(ph);
			ph->id_stock = ph->philosophers[index].id;
			ft_philosopher_is_born(ph, index);
			ft_exit ("01234", NULL, 0, ph);
		}
		else
			index++;
	}
}

void
	*everyone_full(void *content)
{
	t_global	*ph;
	uint32_t	i;

	i = 0;
	ph = ((t_global *)content);
	while (i < ph->philo_nbr)
	{
		sem_wait(ph->sem_done);
		i++;
	}
	sem_post(ph->stop);
	return (NULL);
}
