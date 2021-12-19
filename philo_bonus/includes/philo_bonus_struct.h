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
	int				stop;
	struct s_philo	*philosophers;
	// pthread_t		death;
	sem_t			*forks;
	sem_t			*talk;
	sem_t			*lock;
	int				id_stock;
}				t_global;

#endif