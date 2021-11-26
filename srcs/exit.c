#include "philosophers.h"

void	ft_exit(char *arg, char *text, bool	end)
{
	if(text)
		printf("Error : %s\n", text);
	if(arg)
		exit(end);
	/*
	1 = free s
	2 = free philosophers
	*/
	exit(end);
}