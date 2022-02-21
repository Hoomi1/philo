#include "philo.h"

int	init_value(int argc, char **argv, t_settings *settings)
{
	int	i;

	i = 0;
	settings->num_philo = ft_atoi(argv[1]);
	settings->time_die = ft_atoi(argv[2]) * 1000;
	settings->time_eat = ft_atoi(argv[3]) * 1000;
	settings->time_sleep = ft_atoi(argv[4]) * 1000;
	settings->index_eat = 0;
	if (argc != 6)
		settings->num_must_eat = -1;
	else if (argc == 6)
		settings->num_must_eat = ft_atoi(argv[5]);
	settings->fork = (t_fork *) malloc(sizeof(t_fork) * settings->num_philo);
	if (settings->fork == NULL)
		return (-1);
	while (i < settings->num_philo)
	{
		if (pthread_mutex_init(&settings->fork[i].mutex_t, NULL) != 0)
			return (-1);
		settings->fork[i].status = 0;
		i++;
	}
	if (pthread_mutex_init(&settings->xz, NULL) != 0)
		return (-1);
	return (0);
}

void	write_philo(int index, t_settings *settings, t_philo *philo)
{
	pthread_mutex_lock(&settings->xz);
	if (index == 1)
		printf(" %zu %d has taken a fork\n", \
			get_time() - settings->time_start, philo->num_i + 1);
	else if (index == 2)
		printf(" %zu %d is eating \n", \
			get_time() - settings->time_start, philo->num_i + 1);
	else if (index == 3)
		printf(" %zu %d is sleeping \n", \
			get_time() - settings->time_start, philo->num_i + 1);
	else if (index == 4)
		printf(" %zu %d is is thinking \n", \
			get_time() - settings->time_start, philo->num_i + 1);
	else if (index == 5)
	{
		printf(" %zu ", get_time() - settings->time_start);
		printf("%d died \n", philo->num_i + 1);
	}
	pthread_mutex_unlock(&settings->xz);
}
