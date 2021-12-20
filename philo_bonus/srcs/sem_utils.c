/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:55 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 09:44:55 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_pid(t_global *ph)
{
	uint32_t i;

	i = 0;
	while(i < ph->philo_nbr)
	{
		kill(ph->philosophers[i].pid, SIGKILL);
		i++;
	}
}

void
	close_semaphore(t_global *ph)
{
	sem_close(ph->forks);
	sem_close(ph->lock);
	sem_close(ph->talk);
}

void
	unlink_semaphore(void)
{
	sem_unlink("forks");
	sem_unlink("talk");
	sem_unlink("lock");
}

void
	open_semaphore(t_global *ph)
{
	uint32_t	i;

	i = 0;
	ph->forks = sem_open("forks", O_CREAT, 0644, ph->philo_nbr);
	if (SEM_FAILED == ph->forks)
		printf("Error, {%s}", strerror(errno));
	ph->talk = sem_open("talk", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->talk)
		printf("Error, {%s}", strerror(errno));
	ph->lock = sem_open("lock", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->lock)
		printf("Error, {%s}", strerror(errno)); 
}
