/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:43 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/21 17:47:45 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
