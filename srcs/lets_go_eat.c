#include "philosophers.h"



/*

size_t	__get_time__(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_status(int	id, char *str)
{
	pthread_mutex_lock(&s()->lock);
	printf("[%10lu] : philosopher %d, %s\n", __get_time__() - s()->start_time, id, str);
	if(s()->stop_program == false)
		pthread_mutex_unlock(&s()->lock);
}

void	ft_take_forks(int id)
{
	unsigned int left;
	unsigned int right;

	left = id;
	right = (id + 1) % s()->philo_nbr;
	if(0 == id % 2)
	{
		pthread_mutex_lock(&s()->forks[left]);
		ft_status(id, FORK_LEFT);
		pthread_mutex_lock(&s()->forks[right]);
		ft_status(id, FORK_RIGHT);
	}
	else
	{
		// usleep(50);
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

	left = id;
	right = (id + 1) % s()->philo_nbr;
	if(1 == id % 2)
	{
		pthread_mutex_unlock(&s()->forks[right]);
		ft_status(id, DROP_RIGHT);
		pthread_mutex_unlock(&s()->forks[left]);
		ft_status(id, DROP_LEFT);
	}
	else
	{
		pthread_mutex_unlock(&s()->forks[left]);
		ft_status(id, DROP_LEFT);
		pthread_mutex_unlock(&s()->forks[right]);
		ft_status(id, DROP_RIGHT);
	}
}

void	__usleep(int64_t	time)
{
	const	int64_t instant_t = __get_time__();

	while ((int64_t)__get_time__() - instant_t < time)
		usleep(500);
}

void	ft_is_eating(int id)
{
	ft_status(id, IS_EATING);
	
	pthread_mutex_lock(&s()->lock);
	// printf("ID = %d\n", id);
	s()->philosophers[id].last_meal = __get_time__();
	printf("LAST MEAL = %zu\n", s()->philosophers[id].last_meal);
	s()->philosophers[id].eaten_count++;
	pthread_mutex_unlock(&s()->lock);
	__usleep(s()->time_to_eat);
}

void	ft_is_sleeping(int id)
{
	ft_status(id, IS_SLEEPING);
	__usleep(s()->time_to_sleep);
}





void	ft_is_dead(int id)
{
	// printf("get_time = %lu, mystart = %lu", __get_time__(), s()->start_time);
	printf("[%10lu] : philosopher %d, %s\n", __get_time__() - s()->start_time, id, IS_DEAD);
}


int		ft_is_alive(t_philo	*philo)
{
	pthread_mutex_lock(&s()->lock);
	if (__get_time__() - philo->last_meal < (size_t)s()->time_to_die)
	{
		pthread_mutex_unlock(&s()->lock);
		
		return (SUCCESS);
	}
	printf("is dead");
	printf("gtime = %zu, lastmeal = %zu, timetodie = %zu", __get_time__(), philo->last_meal, (size_t)s()->time_to_die);
	return (ERROR);
}


void	*ft_end_of_program(void	*content)
{
	unsigned int i;

	(void)content;
	i = 0;
	while (1)
	{
		usleep(100);
		if (ERROR == ft_is_alive(&s()->philosophers[i]))
		{
			s()->stop_program = true;
			ft_is_dead(i + 1);
			exit(1);
		}
		i++;
		if (i == s()->philo_nbr)
			i = 0;
	}
	return (NULL);
}





void	*ft_philosopher_is_born(void	*philosopher)
{
	unsigned int id;
	t_philo *philo = ((t_philo *)philosopher);

	id = philo->id;
	pthread_mutex_lock(&s()->lock);
	philo->last_meal = __get_time__();
	pthread_mutex_unlock(&s()->lock);
	while(false == s()->stop_program)
	{
		ft_take_forks(id);
		ft_is_eating(id);
		ft_drop_forks(id);
		ft_is_sleeping(id);
		ft_status(id, IS_THINKING);
		// __usleep(s()->time_to_eat - s()->time_to_sleep);
	}
	return (NULL);
}

*/



void	take_forks(t_philo *philo)
{
	unsigned int 	left;
	unsigned int 	right;
	const uint32_t 	id = philo->id;

	left = id;
	right = (id + 1) % s()->philo_nbr;
	if(0 == id % 2)
	{
		pthread_mutex_lock(&s()->forks[left]);
		pthread_mutex_lock(&s()->forks[right]);
	}
	else
	{
		pthread_mutex_lock(&s()->forks[right]);
		pthread_mutex_lock(&s()->forks[left]);
	}
}

void	drop_forks(t_philo *philo)
{
	unsigned int 	left;
	unsigned int 	right;
	const uint32_t 	id = philo->id;

	left = id;
	right = (id + 1) % s()->philo_nbr;
	if(0 == id % 2)
	{
		pthread_mutex_unlock(&s()->forks[right]);
		pthread_mutex_unlock(&s()->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&s()->forks[left]);
		pthread_mutex_unlock(&s()->forks[right]);
	}
}

size_t	__get_time__(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	__status__(t_philo *philo, int m)
{
	const char *str[4] = {"is dead", "is thinking", "is sleeping", "is eating"};
	pthread_mutex_lock(&s()->talk);
	printf("[%10zu]  %d --> %s\n", __get_time__() - s()->start_time, philo->id, str[m]);
	if (m != 0)
		pthread_mutex_unlock(&s()->talk);
}

size_t	__get_time_micro__(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000000) + (time.tv_usec)));
}



int		is_alive(t_philo *philo)
{
	if (__get_time_micro__() - philo->last_meal <= s()->time_to_die * 1000)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

void	__usleep__(int64_t ms)
{
	size_t	now;

	now = __get_time_micro__();
	while(now - __get_time_micro__() < (size_t)(ms * 1000))
		usleep(500);
}

void	is_eating(t_philo *philo)
{
	__status__(philo, 3);
	pthread_mutex_lock(&philo->lock_meal);
	philo->last_meal = __get_time_micro__();
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->lock_meal);
}

void	is_sleping(t_philo *philo)
{
	__status__(philo, 2);
	__usleep__(s()->time_to_sleep);
}

void	*ft_philosopher_is_born(void	*philosopher)
{
	unsigned int id;
	t_philo *philo = ((t_philo *)philosopher);

	id = philo->id;
	pthread_mutex_lock(&philo->lock_meal);
	philo->last_meal = __get_time_micro__();
	pthread_mutex_unlock(&philo->lock_meal);
	while (false == s()->stop_program)
	{
		take_forks(philo);
		is_eating(philo);
		drop_forks(philo);
		is_sleping(philo);
		__status__(philo, 1);
		// __usleep__(s()->time_to_eat - s()->time_to_sleep);
		// printf("It's working !\n");
	}
	// printf("%zu\n", philo->last_meal);
	return (NULL);
}













void	ft_lets_go_eat(t_global	*ph)
{
	uint32_t i;

	i = 0;
	while(i < ph->philo_nbr)
	{
		pthread_mutex_init(&ph->forks[i], NULL);
		pthread_mutex_init(&ph->philosophers[i].lock_meal, NULL);
		i++;
	}
	pthread_mutex_init(&ph->talk, NULL);
	pthread_mutex_init(&ph->lock, NULL);
	i = 0;
	pthread_mutex_lock(&ph->lock);
	while(i < ph->philo_nbr)
	{
		pthread_create(&ph->philosophers[i].philo, NULL, &ft_philosopher_is_born, &ph->philosophers[i]);
		i++;
	}
	ph->start_time = __get_time__();
	pthread_mutex_unlock(&s()->lock);
	// pthread_create(&ph->checker, NULL, &ft_end_of_program, NULL);
	i = 0;
	while(i < ph->philo_nbr)
		pthread_join(ph->philosophers[i++].philo, NULL);
}


