/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:16:49 by mamaurai          #+#    #+#             */
/*   Updated: 2021/12/14 17:16:50 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	__free_struct__(t_global *ph)
{
	free(ph);
}

static void	__free_mutex__(t_global *ph)
{
	free(ph->forks);
}

static void __free_phi__(t_global *ph)
{
	free(ph->philosophers);
}


void	ft_exit(char *arg, char *text, bool	end, t_global *ph)
{
	uint32_t i;
	void (*f[3])() = {__free_mutex__, __free_phi__, __free_struct__};

	i = 0;
	if(text)
		printf("Error : %s\n", text);
	if(arg)
		exit(end);
	while(arg[i])
	{
		(f[arg[i] - 48])(ph);
		i++;
	}
	exit(end);
}