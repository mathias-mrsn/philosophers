/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:44:48 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 09:44:49 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void
	*alloc(t_global *ph)
{
	
	ph->philosophers = malloc(sizeof(t_philo) * ph->philo_nbr);
	if(!ph->philosophers)
		return (free(ph), NULL);
	return (ph);
}

void
	quit(t_global *ph)
{
	// close_semaphore(ph);
	// unlink_semaphore();
	// close_pid(ph);
	if (ph->philosophers)
		free(ph->philosophers);
	if (ph)
		free(ph);
}
