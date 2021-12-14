/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_struct.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:44 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/14 17:16:45 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCT_H
# define PHILOSOPHERS_STRUCT_H

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		philo;	
	bool			state;
	size_t			last_meal;
	unsigned int	eaten_count;	
	uint64_t		recalibration;		
}				t_philo;

typedef struct s_global
{
	uint32_t		philo_nbr;
	uint32_t		time_to_eat;
	uint32_t		time_to_die;
	uint32_t		time_to_sleep;
	uint32_t		times_must_eat;
	uint32_t		set_id;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t lock;
	pthread_mutex_t talk;
	struct s_philo	*philosophers;

}				t_global;

#endif
