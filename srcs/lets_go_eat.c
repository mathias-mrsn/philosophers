#include "philosophers.h"

size_t	ft_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_status(int	id, char *str)
{
	pthread_mutex_lock(&s()->lock);
	printf("[%10lu] : philosopher %d, %s\n", ft_get_time() - s()->start_time, id, str);
	if(s()->stop_program == false)
		pthread_mutex_unlock(&s()->lock);
}

// int		ft_keep_going(t_philo *philo)
// {
// 	size_t time = ft_get_time();

// 	// printf("time = %lu, last meal = %lu, id = %d, stop = %d\n", time, philo->last_meal, philo->id, s()->stop_program);
// 	pthread_mutex_lock(&s()->lock);
// 	if((size_t)(time - philo->last_meal) < (size_t)(s()->time_to_die))
// 	{
// 		pthread_mutex_unlock(&s()->lock);
// 		return (SUCCESS);
// 	}
// 	s()->stop_program = true;
// 	pthread_mutex_unlock(&s()->lock);
// 	ft_status(philo->id, IS_DEAD);
// 	exit(0);
// 	return (ERROR);
// }

void	ft_take_forks(int id)
{
	unsigned int left;
	unsigned int right;

	left = id - 1;
	right = (id) % s()->philo_nbr;
	printf("left = %d, right = %d, id = %d\n", left, right, id);
	if(1 == id % 2)
	{
		pthread_mutex_lock(&s()->forks[left]);
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

	left = id - 1;
	right = (id) % s()->philo_nbr;
	if(1 == id % 2)
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

void	__usleep(size_t	time)
{
	const	uint64_t instant_t = ft_get_time();

	while (ft_get_time() - instant_t < time)
		usleep(500);
}

void	ft_is_eating(int id)
{
	ft_status(id, IS_EATING);
	
	pthread_mutex_lock(&s()->lock);
	s()->philosophers[id - 1].last_meal = ft_get_time();
	s()->philosophers[id - 1].eaten_count++;
	pthread_mutex_unlock(&s()->lock);
	__usleep(s()->time_to_eat);
	// usleep(s()->time_to_eat * 1000);
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
	while(false == s()->stop_program)
	{
		printf("new loop | id = %d\n", id);
		ft_take_forks(id);
		ft_is_eating(id);
		ft_drop_forks(id);
		ft_is_sleeping(id);
		ft_status(id, IS_THINKING);
	}
	return (NULL);
}






int		ft_is_alive(t_philo	*philo)
{
	if (ft_get_time() - philo->last_meal <= s()->time_to_die)
		return (SUCCESS);
	return (ERROR);
}

void	*ft_end_of_program(void	*content)
{
	unsigned int i;

	i = 0;
	if(content == NULL)
		i = 0;
	while(false == s()->stop_program)
	{
		pthread_mutex_lock(&s()->lock);
		if (ERROR == ft_is_alive(&s()->philosophers[i])/* && s()->philosophers[i].eaten_count >= s()->times_must_eat*/)
		{
			s()->stop_program = true;
			pthread_mutex_unlock(&s()->lock);
			ft_status(i + 1, IS_DEAD);
			exit(1);
		}
		pthread_mutex_unlock(&s()->lock);
		i++;
		if (i == s()->philo_nbr)
			i = 0;
		// printf("[10%lu]", ft_get_time());
	}
	return (NULL);
}

void	ft_lets_go_eat(t_global	*ph)
{
	static unsigned int i = 0;

	while(i < ph->philo_nbr)
	{
		pthread_mutex_init(&ph->forks[i], NULL);
		i++;
	}
	i = 0;
	ph->start_time = ft_get_time();
	while(i < ph->philo_nbr)
	{
		pthread_create(&ph->philosophers[i].philo, NULL, &ft_philosopher_is_born, &ph->philosophers[i]);
		i++;
	}
	pthread_create(&ph->checker, NULL, &ft_end_of_program, NULL);
	pthread_mutex_init(&ph->lock, NULL);
	i = 0;
	while(i < ph->philo_nbr)
		pthread_join(ph->philosophers[i++].philo, NULL);
}