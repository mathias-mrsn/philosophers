/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:15:48 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/21 22:06:08 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int
	__free_phi__(t_global *ph)
{
	free(ph->philosophers);
	return (0);
}

static int
	__free_sem__(t_global *ph)
{
	close_semaphore(ph);
	unlink_semaphore();
	return (0);
}

static int
	__free_struct__(t_global *ph)
{
	free(ph);
	return (0);
}

int
	unlink_semaphore(void)
{
	sem_unlink("forks");
	sem_unlink("talk");
	sem_unlink("lock");
	sem_unlink("stop");
	sem_unlink("sem_done");
	return (0);
}

void
	ft_exit(char *arg, char *text, int end, t_global *ph)
{
	uint32_t	i;
	static int	(*f[5])() = {__free_sem__, __free_phi__,
		close_semaphore, unlink_semaphore, __free_struct__};

	i = 0;
	if (text)
		printf("Error : %s\n", text);
	while (arg[i])
	{
		(f[arg[i] - 48])(ph);
		i++;
	}
	exit(end);
}
