/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:43 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/22 14:41:52 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	ft_start_meal(t_global *ph)
{
	uint32_t	index;
	uint32_t	id;
	pthread_t	full_monitor;

	index = 0;
	id = 0;
	sem_wait(ph->stop);
	ph->start_time = __get_time__();
	if (ph->times_must_eat != 0)
	{
		start_philo(ph);
		if (pthread_create(&full_monitor, NULL, &everyone_full, ph) != 0)
			return ;
		pthread_join(full_monitor, NULL);
	}
	index = 0;
	while (index < ph->philo_nbr)
	{
		waitpid(-1, NULL, 0);
		index++;
	}
	ft_exit("01234", NULL, 0, ph);
}

int
	main(int ac, char **av)
{
	t_global	*ph;

	ph = malloc(sizeof(t_global));
	if (!ph)
		return (0);
	memset(ph, 0, sizeof(t_global));
	ph->times_must_eat = -1;
	ft_parsing(ac, av, ph);
	unlink_semaphore();
	open_semaphore(ph);
	if (!alloc(ph))
		return (1);
	ft_start_meal(ph);
}
