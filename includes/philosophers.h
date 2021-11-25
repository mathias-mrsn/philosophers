#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INT32MAX_SIZE 11

# define SUCCESS 0
# define ERROR 1

# define INVALID (-1)

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h> //mutex and threads
# include "philosophers_struct.h"

/*	PARSING		*/

void	ft_parsing(int ac, char **av, t_global *p);

/*	FREE		*/

void	ft_free(char *arg, char *text, bool	end);

#endif