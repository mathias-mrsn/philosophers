#include "philosophers.h"

void	print___(void)
{
	static unsigned int i = -1;
	printf("S_GLOBAL : \nphilo_nbr = %d\ntime_to_eat = %d\ntime_to_die = %d\ntime_to_sleep = %d\ntime_must_eat = %d\n\n\n", s()->philo_nbr, s()->time_to_eat, s()->time_to_die, s()->time_to_sleep, s()->times_must_eat);
	while(++i < s()->philo_nbr)
	{
		printf("PHILOSOPHERS N.%d\n", i);
		printf("id = %d\n", s()->philosophers[i].id);
		printf("last_meal = %lu\n\n", s()->philosophers[i].last_meal);
	}
	i = -1;
}

void	__ft_alloc__(t_global	*ph)
{
	static size_t	i = 0;

	ph->philosophers = malloc(ph->philo_nbr * sizeof(t_philo));
	if(!ph->philosophers)
		ft_exit("1", "malloc error", ERROR);
	ph->forks = malloc(ph->philo_nbr * sizeof(pthread_mutex_t));
	if(!ph->forks)
		ft_exit("12", "malloc error", ERROR);
	while(i < ph->philo_nbr)
	{
		memset(&ph->philosophers[i], 0, sizeof(t_philo));
		ph->philosophers[i].id = i + 1;
		i++;
	}
}

t_global	*s(void)
{
	static t_global *s = NULL;

	if (!s)
	{
		s = malloc(sizeof(t_global));
		if (!s)
			return (free(s), NULL);
		memset(s, 0, sizeof(t_global));
	}
	return (s);
}

int	main(int ac, char **av)
{
	if(!s())
		return (ERROR);
	ft_parsing(ac, av, s());
	__ft_alloc__(s());
	print___();
	ft_lets_go_eat(s());
}