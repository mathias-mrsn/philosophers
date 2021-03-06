/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:28:32 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/23 08:49:16 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		philo;	
	int				state;
	size_t			last_meal;
	pthread_mutex_t	lock_philo;
	unsigned int	eaten_count;	
}				t_philo;

typedef struct s_global
{
	uint32_t		philo_nbr;
	uint32_t		time_to_eat;
	uint32_t		time_to_die;
	uint32_t		time_to_sleep;
	int64_t			times_must_eat;
	uint32_t		set_id;
	size_t			start_time;
	uint32_t		philo_done;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	talk;
	int				stop_talking;
	pthread_t		death;
	struct s_philo	*philosophers;

}				t_global;

#endif
