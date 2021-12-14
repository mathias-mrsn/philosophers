#include "philosophers.h"

static unsigned int	__ft_atoi_lite__(const char *str)
{
	int	i;
	int	neg;
	unsigned int	res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

static unsigned int	__ft_get_arg__(char *arg)
{
	unsigned int i;

	i = 0;
	while(arg[i])
	{
		if(arg[i] < '0' || arg[i] > '9' || i >= INT32MAX_SIZE)
			return (INVALID);
		i++;
	}
	if(i == 0)
		return (INVALID);
	return (__ft_atoi_lite__(arg));
}

static bool	__ft_check_arg__(t_global *ph)
{
	if(ph->philo_nbr == (unsigned int)INVALID 
		|| ph->time_to_die == (unsigned int)INVALID 
		|| ph->time_to_eat == (unsigned int)INVALID 
		|| ph->time_to_sleep == (unsigned int)INVALID 
		|| ph->times_must_eat == (unsigned int)INVALID)
		return (ERROR);
	return (SUCCESS);

}

void	ft_parsing(int ac, char **av, t_global *ph)
{
	if (ac != 6 && ac != 5)
		ft_exit("1", "arguments number incorrect", ERROR, ph);
	ph->philo_nbr = __ft_get_arg__(av[1]);
	ph->time_to_die = __ft_get_arg__(av[2]);
	ph->time_to_eat = __ft_get_arg__(av[3]);
	ph->time_to_sleep = __ft_get_arg__(av[4]);
	if (ac == 6)
		ph->times_must_eat = __ft_get_arg__(av[5]);
	if(__ft_check_arg__(ph) == ERROR)
		ft_exit("1", "wrong argument", ERROR, ph);	
}