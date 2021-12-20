/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:53 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 09:45:33 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void
	*death(void	*content)
{
	t_global	*ph;
	uint32_t	i;
	int			test;

	i = 0;
	ph = ((t_global *)content);
	__usleep__(ph->time_to_die);
	while (1)
	{
		usleep(100);
		test = __still_alive__(&ph->philosophers[ph->id_stock], ph);
		if (ph->philosophers[i].state != 2 && ERROR == test)
		{		
			exit(0);
		}
		i++;
		if (i == ph->philo_nbr)
			i = 0;
	}
}

static void
	*ft_philosopher_is_born(t_global *ph, const uint32_t id)
{
	pthread_t	monitor;

	sem_wait(ph->lock);
	ph->philosophers[id].last_meal = __get_time__();
	ph->id_stock = id;
	sem_post(ph->lock);
	if (pthread_create(&monitor, NULL, &death, ph))
		return (NULL);
	if (0 == (id % 2) && ph->philo_nbr > 1)
		__usleep__(ph->time_to_eat);
	while (!ph->stop && (-1 == ph->times_must_eat
		|| ph->philosophers[id].eaten_count < ph->times_must_eat))
	{
		ft_take_forks(&ph->philosophers[id], ph);
		ft_is_eating(&ph->philosophers[id], ph);
		ft_drop_forks(ph);
		ft_is_sleeping(&ph->philosophers[id], ph);
		__status__(ph->philosophers[id].id, 4, ph);
		__usleep__((size_t)(ph->time_to_eat - ph->time_to_sleep));
	}
	return (NULL);
}

void
	ft_start_meal(t_global *ph)
{
	uint32_t index;
	uint32_t id;

	index = 0;
	id = 0;
	sem_wait(ph->lock);
	ph->start_time = __get_time__();
	while(index < ph->philo_nbr)
	{
		ph->philosophers[index].id = id++;
		ph->philosophers[index].pid = fork();
		if (ph->philosophers[index].pid < 0)
			return ;
		else if (ph->philosophers[index].pid == 0)
		{
			ft_philosopher_is_born(ph, index);
			exit(0);
		}
		else
			index++;
	}
	sem_post(ph->lock);
	index = 0;
	waitpid(-1, NULL, 0);
	quit(ph);
}