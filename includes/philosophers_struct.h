#ifndef PHILOSOPHERS_STRUCT_H
# define PHILOSOPHERS_STRUCT_H

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		philo;	
	bool			state;
	size_t			last_meal;
	unsigned int	eaten_count;			
}				t_philo;

typedef struct s_global
{
	unsigned int	philo_nbr;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	times_must_eat;
	bool			stop_program;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t lock;
	pthread_t		checker;
	struct s_philo	*philosophers;

}				t_global;

#endif
