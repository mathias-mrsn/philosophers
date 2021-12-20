/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:51 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 22:08:06 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	__ft_alloc__(t_global	*ph)
{
	uint32_t	i;

	i = 0;
	ph->philosophers = malloc(ph->philo_nbr * sizeof(t_philo));
	if (!ph->philosophers)
		ft_exit("2", "malloc error", ERROR, ph);
	ph->forks = malloc(ph->philo_nbr * sizeof(pthread_mutex_t));
	if (!ph->forks)
		ft_exit("12", "malloc error", ERROR, ph);
	while (i < ph->philo_nbr)
	{
		memset(&ph->philosophers[i], 0, sizeof(t_philo));
		ph->philosophers[i].id = i;
		i++;
	}
}

int
	main(int ac, char **av)
{
	t_global	*s;

	s = NULL;
	s = malloc(sizeof(t_global));
	if (!s)
		return (0);
	memset(s, 0, sizeof(t_global));
	s->times_must_eat = -1;
	ft_parsing(ac, av, s);
	__ft_alloc__(s);
	ft_lets_go_eat(s);
	ft_exit("123", NULL, SUCCESS, s);
	return (0);
}
