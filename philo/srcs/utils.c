#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *s)
{
	int		res;
	int		sign;
	int		i;
	char	*str;

	res = 0;
	sign = 1;
	i = 0;
	str = (char *)s;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (i >= 20 && sign == 1)
			res = -1;
		if (i >= 20 && sign == -1)
			res = 0;
	}
	return (res * sign);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	my_destroy_mutex(t_settings *g_settings)
{
	int	i;

	i = 0;
	if (g_settings)
	{
		while (i < g_settings->num_philo)
		{
			if (pthread_mutex_destroy(&g_settings->fork[i].mutex_t) != 0)
				return (-1);
			i ++;
		}
		free(g_settings->fork);
		if (pthread_mutex_destroy(&g_settings->xz) != 0)
			return (-1);
		free(g_settings);
	}
	return (0);
}

int	destoy_human(t_philo *philo, t_settings *g_settings)
{
	int	i;

	i = 0;
	if (philo)
	{
		while (i < g_settings->num_philo)
		{
			if (pthread_detach(philo[i].thread) != 0)
				return (-1);
			i++;
		}
		free(philo);
	}
	if (my_destroy_mutex(g_settings) == -1)
		return (-1);
	return (0);
}
