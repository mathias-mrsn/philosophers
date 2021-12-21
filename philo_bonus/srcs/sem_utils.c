/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:55 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/21 23:37:30 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_pid(t_global *ph)
{
	uint32_t	i;

	i = 0;
	while (i < ph->philo_nbr)
	{
		kill(ph->philosophers[i].pid, SIGKILL);
		i++;
	}
}

int
	close_semaphore(t_global *ph)
{
	sem_close(ph->forks);
	sem_close(ph->lock);
	sem_close(ph->talk);
	sem_close(ph->stop);
	sem_close(ph->sem_done);
	return (1);
}

void
	open_semaphore(t_global *ph)
{
	uint32_t	i;
	int			failure;

	i = 0;
	failure = 0;
	ph->forks = sem_open("forks", O_CREAT, 0644, ph->philo_nbr);
	if (SEM_FAILED == ph->forks)
		failure = 1;
	ph->talk = sem_open("talk", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->talk)
		failure = 1;
	ph->lock = sem_open("lock", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->lock)
		failure = 1;
	ph->stop = sem_open("stop", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->stop)
		failure = 1;
	ph->sem_done = sem_open("sem_done", O_CREAT, 0644, 0);
	if (SEM_FAILED == ph->sem_done)
		failure = 1;
	if (failure)
		ft_exit("12345", NULL, 1, ph);
}
