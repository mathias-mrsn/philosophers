/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_struct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:17:40 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/21 18:17:41 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_STRUCT_H
# define PHILO_BONUS_STRUCT_H

typedef struct s_philo
{
	unsigned int	id;
	pid_t			pid;
	size_t			last_meal;
	int				state;
	unsigned int	eaten_count;		
}				t_philo;

typedef struct s_global
{
	uint32_t		philo_nbr;
	uint32_t		time_to_eat;
	uint32_t		time_to_die;
	uint32_t		time_to_sleep;
	int64_t			times_must_eat;
	size_t			start_time;
	sem_t			*stop;
	int				stop_value;
	struct s_philo	*philosophers;
	sem_t			*forks;
	sem_t			*talk;
	int				stop_talking;
	sem_t			*lock;
	int				id_stock;
}				t_global;

#endif