#include "philo.h"

static int	pars_str(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_value(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("Few arguments\n");
		else if (argc > 6)
			printf("Many arguments\n");
		return (-1);
	}
	if (pars_str(argv) == -1)
	{
		printf("Arguments are numbers only\n");
		return (-1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("At least once philosophers eat\n");
		return (-1);
	}
	return (0);
}
