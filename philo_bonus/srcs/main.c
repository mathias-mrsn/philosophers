#include "philo_bonus.h"

void	close_pid(t_global *ph)
{
	uint32_t i;

	i = 0;
	while(i < ph->philo_nbr)
	{
		// printf("%d\n", ph->id_stock);
		if (i != ph->id_stock)
			kill(ph->philosophers[i].pid, SIGTERM);
		i++;
	}
}


size_t	__get_time__(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}


void	__status__(int id, int status, t_global *ph)
{
	const char	*stat[5] = {DEAD, FORK, EAT, SLEEP, THINK};
	const char	*colors[5] = {"\x1B[31m", "\x1B[33m",
		"\x1B[32m", "\x1B[36m", "\x1B[35m"};

	sem_wait(ph->talk);
	printf("[%8lu] %d %s%s\033[0m\n",
		(__get_time__() - ph->start_time), id, colors[status], stat[status]);
	if (status != 0)
		sem_post(ph->talk);
}


int	__still_alive__(t_philo	*philo, t_global *ph)
{
	// printf("%zu\n", philo->last_meal);
	if (__get_time__() - philo->last_meal <= (uint64_t)ph->time_to_die)
		return (SUCCESS);
	__status__(philo->id, 0, ph);
	return (ERROR);
}


void	__usleep__(size_t	time)
{
	const size_t	instant_t = __get_time__();

	while (__get_time__() - instant_t < time)
		usleep(500);
}


void	ft_is_eating(t_philo *philo, t_global *ph)
{
	__status__(philo->id, 2, ph);
	sem_wait(ph->lock);
	philo->last_meal = __get_time__();
	philo->eaten_count++;
	if (philo->eaten_count == ph->times_must_eat)
		philo->state = 2;
	sem_post(ph->lock);
	__usleep__(ph->time_to_eat);
}


void	ft_is_sleeping(t_philo *philo, t_global *ph)
{
	__status__(philo->id, 3, ph);
	__usleep__(ph->time_to_sleep);
}


void	ft_take_forks(t_philo *philo, t_global *ph)
{
	sem_wait(ph->forks);
	__status__(philo->id, 1, ph);
	sem_wait(ph->forks);
	__status__(philo->id, 1, ph);

}


void	ft_drop_forks(t_global *ph)
{
	sem_post(ph->forks);
	sem_post(ph->forks);

}



static void	*death(void	*content)
{
	t_global	*ph;
	uint32_t	i;
	int			test;

	i = 0;
	ph = ((t_global *)content);
	__usleep__(ph->time_to_die);
	while (1)
	{
		usleep(100);
		test = __still_alive__(&ph->philosophers[ph->id_stock], ph);
		if (ph->philosophers[i].state != 2 && ERROR == test)
		{
			close_pid(ph);
			exit(0);
		}
		i++;
		if (i == ph->philo_nbr)
			i = 0;
	}
}

static void	*ft_philosopher_is_born(t_global *ph, const uint32_t id)
{
	int save = 0;
	pthread_t	monitor;

	sem_wait(ph->lock);
	ph->philosophers[id].last_meal = __get_time__();
	ph->id_stock = id;
	sem_post(ph->lock);
	if (pthread_create(&monitor, NULL, &death, ph))
		return (NULL);
	if (0 == (id % 2) && ph->philo_nbr > 1)
		__usleep__(ph->time_to_eat);
	while (!ph->stop && (-1 == ph->times_must_eat
		|| ph->philosophers[id].eaten_count < ph->times_must_eat))
	{
		ft_take_forks(&ph->philosophers[id], ph);
		ft_is_eating(&ph->philosophers[id], ph);
		ft_drop_forks(ph);
		ft_is_sleeping(&ph->philosophers[id], ph);
		__status__(ph->philosophers[id].id, 4, ph);
		__usleep__((size_t)(ph->time_to_eat - ph->time_to_sleep));
	}
	return (NULL);
}


void	close_semaphore(t_global *ph)
{
	sem_close(ph->forks);
	sem_close(ph->lock);
	sem_close(ph->talk);
}


void	unlink_semaphore(void)
{
	sem_unlink("forks");
	sem_unlink("talk");
	sem_unlink("lock");
}


void	alloc(t_global *ph)
{
	ph->philosophers = malloc(sizeof(t_philo) * ph->philo_nbr);
	if(!ph->philosophers)
		return ;
}


void	open_semaphore(t_global *ph)
{
	uint32_t	i;

	i = 0;
	ph->forks = sem_open("forks", O_CREAT, 0644, ph->philo_nbr);
	if(SEM_FAILED == ph->forks)
		printf("Error, {%s}", strerror(errno));
	ph->talk = sem_open("talk", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->talk)
		printf("Error, {%s}", strerror(errno));
	ph->lock = sem_open("lock", O_CREAT, 0644, 1);
	if (SEM_FAILED == ph->lock)
		printf("Error, {%s}", strerror(errno)); 
}


void	ft_start_meal(t_global *ph)
{
	uint32_t index;
	uint32_t id;

	index = 0;
	id = 0;
	sem_wait(ph->lock);
	ph->start_time = __get_time__();
	while(index < ph->philo_nbr)
	{
		ph->philosophers[index].id = id++;
		ph->philosophers[index].pid = fork();
		if (ph->philosophers[index].pid < 0)
			return ;
		else if (ph->philosophers[index].pid == 0)
		{
			// open_semaphore(ph);
			ft_philosopher_is_born(ph, index);
			// close_semaphore(ph);
			exit(0);
		}
		else
			index++;
	}
	sem_post(ph->lock);
	index = 0;
	while(index < ph->philo_nbr)
		waitpid(ph->philosophers[index++].pid, NULL, 0);
}


int main(int ac, char **av)
{
	t_global	*ph;

	ph = malloc(sizeof(t_global));
	if (!ph)
		return (0);
	memset(ph, 0, sizeof(t_global));
	ph->times_must_eat = -1;
	ft_parsing(ac, av, ph);
	unlink_semaphore();
	open_semaphore(ph);
	alloc(ph);
	ft_start_meal(ph);
	// close_pid(ph);
}
