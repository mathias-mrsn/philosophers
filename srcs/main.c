#include "philosophers.h"

void	ft_free(char *arg, char *text, bool	end)
{
	if(text)
		printf("Error : %s\n", text);
	if(arg)
		exit(end);
	/*
	1 = free s


	*/
	exit(end);
}

t_global	*s(void)
{
	static t_global *s = NULL;

	if (!s)
	{
		s = malloc(sizeof(t_global));
		if (!s)
			return (free(s), NULL);
	}
	return (s);
}

int	main(int ac, char **av)
{
	if(!s())
		return (ERROR);
	ft_parsing(ac, av, s());
	
}