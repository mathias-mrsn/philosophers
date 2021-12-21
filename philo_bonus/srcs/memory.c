/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:48 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/21 18:12:58 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	*alloc(t_global *ph)
{
	uint32_t	i;

	i = 0;
	ph->philosophers = malloc(sizeof(t_philo) * ph->philo_nbr);
	if (!ph->philosophers)
		return (free(ph), NULL);
	while (i < ph->philo_nbr)
		memset(&ph->philosophers[i++], 0, sizeof(t_philo));
	return (ph);
}
