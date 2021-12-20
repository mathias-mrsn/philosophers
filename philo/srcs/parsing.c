/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:52 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/20 22:07:31 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	__print_err__(void)
{
	printf("Incorrect syntax\n");
	printf("./philo ");
	printf(" [number_of_philosophers <0-200> ]");
	printf(" [time_to_die <+60> ]");
	printf(" [time_to_eat <+60> ]");
	printf(" [time_to_sleep <+60> ]");
	printf(" (number_of_times_each_philosopher_must_eat <+0> )\n");
}

static int64_t
	__ft_atol_lite__(const char *str)
{
	int		i;
	int		neg;
	int64_t	res;

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

static uint32_t
	__ft_get_arg__(char *arg)
{
	uint32_t	i;
	int64_t		value;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9' || i >= INT32MAX_SIZE)
			return (INVALID);
		i++;
	}
	if (i == 0)
		return (INVALID);
	value = __ft_atol_lite__(arg);
	if (value > INT_MAX || value < 0)
		return (INVALID);
	return (value);
}

static int
	__ft_check_arg__(t_global *ph)
{
	if (ph->philo_nbr == (unsigned int)INVALID
		|| ph->time_to_die == (unsigned int)INVALID
		|| ph->time_to_eat == (unsigned int)INVALID
		|| ph->time_to_sleep == (unsigned int)INVALID
		|| ph->times_must_eat == (unsigned int)INVALID
		|| ph->philo_nbr > 200 || ph->time_to_sleep < 60
		|| ph->time_to_die < 60 || ph->time_to_eat < 60)
		return (__print_err__(), ERROR);
	return (SUCCESS);
}

void
	ft_parsing(int ac, char **av, t_global *ph)
{
	if (ac != 6 && ac != 5)
	{
		__print_err__();
		ft_exit("2", NULL, ERROR, ph);
	}
	ph->philo_nbr = __ft_get_arg__(av[1]);
	ph->time_to_die = __ft_get_arg__(av[2]);
	ph->time_to_eat = __ft_get_arg__(av[3]);
	ph->time_to_sleep = __ft_get_arg__(av[4]);
	if (ac == 6)
		ph->times_must_eat = __ft_get_arg__(av[5]);
	if (__ft_check_arg__(ph) == ERROR)
		ft_exit("2", NULL, ERROR, ph);
}
