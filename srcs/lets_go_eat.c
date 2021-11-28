#include "philosophers.h"

int		ft_keep_going(t_philo *philo)
{
	size_t time = ft_get_time();

	if(!s()->stop_program && (size_t)(time - philo->last_meal) < (size_t)(s()->time_to_die))
	{
		return (SUCCESS);
	}
	
	ft_status(philo->id, IS_DEAD);
	return (ERROR);
}

size_t	ft_get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_status(int	id, char *str)
{
	printf("[%10lu] : philosopher %d, %s\n", ft_get_time() - s()->start_time, id, str);
}

int		ft_get_fork_left(int id)
{
	return (id);
}

int		ft_get_fork_right(int id)
{
	int fork;

	fork = (id + 1) % s()->philo_nbr;
	return (fork);
}

void	ft_take_forks(int id)
{
	unsigned int left;
	unsigned int right;

	left = ft_get_fork_left(id);
	right = ft_get_fork_right(id);
	if(0 == id % 2)
	{
		pthread_mutex_lock(&s()->forks[left]);
		ft_keep_going(id);
		ft_status(id, FORK_LEFT);
		pthread_mutex_lock(&s()->forks[right]);
		ft_status(id, FORK_RIGHT);
	}
	else
	{
		pthread_mutex_lock(&s()->forks[right]);
		ft_status(id, FORK_RIGHT);
		pthread_mutex_lock(&s()->forks[left]);
		ft_status(id, FORK_LEFT);
	}

}

void	ft_drop_forks(int id)
{
	unsigned int left;
	unsigned int right;

	left = ft_get_fork_left(id);
	right = ft_get_fork_right(id);
	if(0 == id % 2)
	{
		pthread_mutex_unlock(&s()->forks[right]);
		ft_status(id, DROP_LEFT);
		pthread_mutex_unlock(&s()->forks[left]);
		ft_status(id, DROP_RIGHT);
	}
	else
	{
		pthread_mutex_unlock(&s()->forks[left]);
		ft_status(id, DROP_RIGHT);
		pthread_mutex_unlock(&s()->forks[right]);
		ft_status(id, DROP_LEFT);
	}
}

void	ft_is_eating(int id)
{
	ft_status(id, IS_EATING);
	usleep(s()->time_to_eat * 1000);
	s()->philosophers[id].last_meal = ft_get_time();
}

void	ft_is_thinking(int id)
{
	ft_status(id, IS_THINKING);
	usleep(100);
}

void	ft_is_sleeping(int id)
{
	ft_status(id, IS_SLEEPING);
	usleep(s()->time_to_sleep * 1000);
}



void	*ft_philosopher_is_born(void	*philosopher)
{
	unsigned int id;
	t_philo *philo = ((t_philo *)philosopher);

	id = philo->id;
	philo->last_meal = ft_get_time();
	if (1 == s()->philo_nbr)
	{
		usleep(s()->time_to_die * 1000);
		ft_status(id, IS_DEAD);
	}
	while(SUCCESS == ft_keep_going(philo))
	{
		ft_take_forks(id);
		ft_is_eating(id);
		ft_drop_forks(id);
		// ft_is_thinking(id);
		ft_is_sleeping(id);
	}
	return (NULL);
}

void	ft_lets_go_eat(t_global	*ph)
{
	static unsigned int _i = 0;

	ph->start_time = ft_get_time();
	while(_i < ph->philo_nbr)
	{
		pthread_mutex_init(&ph->forks[_i], NULL);
		pthread_create(&ph->philosophers[_i].philo, NULL, &ft_philosopher_is_born, &ph->philosophers[_i]);
		_i++;
	}
	_i = 0;
	while(_i < ph->philo_nbr)
		pthread_join(ph->philosophers[_i++].philo, NULL);
}