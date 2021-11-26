#include "philosophers.h"

void	*ft_philosopher_is_born(void	*philosopher)
{
	// unsigned int i = 0;
	unsigned int id = ((t_philo *)philosopher)->id;

	printf("1%d\n", id);
	// while(i < 10)
	// {
	// 	usleep(100);
	// 	printf("Je suis le philosopher %d J'attends depuis %d", ((t_philo *)philosopher)->id, i);
	// 	i++;
	// }
	return (NULL);
}

void	ft_lets_go_eat(t_global	*ph)
{
	static unsigned int _i = 0;

	while(_i < ph->philo_nbr)
	{
		pthread_create(&ph->philosophers[_i].philo, NULL, &ft_philosopher_is_born, &ph->philosophers[_i]);
		_i++;
	}
}