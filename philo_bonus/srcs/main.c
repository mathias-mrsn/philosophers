#include "philo_bonus.h"

void	close_pid(t_global *ph)
{
	uint32_t i;

	i = 0;
	while(i < ph->philo_nbr)
	{
		kill(ph->philosophers[i].pid, SIGKILL);
		i++;
	}
}

size_t	__get_time_micro__(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)((time.tv_sec * 1000000) + (time.tv_usec)));
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

	sem_wait(ph->talk);
	printf("[%10lu] : philosopher %d, %s\n",
		(__get_time_micro__() - ph->start_time) / 1000, id, stat[status]);
	if (status != 0)
		sem_post(ph->talk);
}

int	__still_alive__(t_philo	*philo, t_global *ph)
{
	uint64_t	isdead;

	isdead = __get_time__() - philo->last_meal;
	if (isdead <= (uint64_t)ph->time_to_die)
		return (SUCCESS);
	__status__(philo->id, 0, ph);
	return (ERROR);
}

void	__usleep__(t_philo *philo, size_t	time, t_global *ph)
{
	const size_t	instant_t = __get_time__();

	while (SUCCESS == __still_alive__(philo, ph)
		&& __get_time__() - instant_t < time)
		usleep(750);
}

void	ft_is_eating(t_philo *philo, t_global *ph)
{
	__status__(philo->id, 2, ph);
	philo->last_meal = __get_time__();
	philo->eaten_count++;
	__usleep__(philo, ph->time_to_eat, ph);
}

void	ft_is_sleeping(t_philo *philo, t_global *ph)
{
	__status__(philo->id, 3, ph);
	__usleep__(philo, ph->time_to_sleep, ph);
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

static void	*ft_philosopher_is_born(t_global *ph, const uint32_t id)
{
	int save = 0;

	sem_wait(ph->lock);
	sem_post(ph->lock);
	ph->philosophers[id].last_meal = __get_time__();
	if (ph->philo_nbr == 1)
	{
		__status__(ph->philosophers[id].id, 1, ph);
		return (__usleep__(&ph->philosophers[id], (size_t)INT_MAX, ph), NULL);
	}
	while (SUCCESS == __still_alive__(&ph->philosophers[id], ph)
		&& (!ph->times_must_eat
			|| ph->philosophers[id].eaten_count < ph->times_must_eat))
	{
		ft_take_forks(&ph->philosophers[id], ph);
		ft_is_eating(&ph->philosophers[id], ph);
		ft_drop_forks(ph);
		ft_is_sleeping(&ph->philosophers[id], ph);
		__status__(ph->philosophers[id].id, 4, ph);
		__usleep__(&ph->philosophers[id],
			(size_t)(ph->time_to_eat - ph->time_to_sleep), ph);
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
	ph->start_time = __get_time_micro__();
	while(index < ph->philo_nbr)
	{
		ph->philosophers[index].pid = fork();
		ph->philosophers[index].id = id++;
		if (ph->philosophers[index].pid < 0)
			return ; //Error
		else if (ph->philosophers[index].pid == 0)
		{
			ft_philosopher_is_born(ph, index);
			exit(0);
		}
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
	ft_parsing(ac, av, ph);
	unlink_semaphore();
	open_semaphore(ph);
	alloc(ph);
	ft_start_meal(ph);
	close_pid(ph);
}