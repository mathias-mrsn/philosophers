#ifndef PHILOSOPHERS_STRUCT_H
# define PHILOSOPHERS_STRUCT_H

typedef struct s_philo
{
	unsigned int	id;
}				t_philo;

typedef struct s_global
{
	unsigned int	philo_nbr;
	unsigned int	time_to_eat;
	unsigned int	time_to_think;
	unsigned int	time_to_sleep;
	unsigned int	times_must_eat;
	// struct s_philo	*philosophers;

}				t_global;

#endif