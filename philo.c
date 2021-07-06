/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:14:34 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/06 20:51:53 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec);
}

int pars_str(int argc, char **argv)
{
	int i;
	int j;
	
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
	
	if (argc < 5 ||  argc > 6)
	{
		if (argc < 5)
			printf("Few arguments\n");
		else if (argc > 6)
			printf("Many arguments\n");
		return (-1);
	}
	if (pars_str(argc, argv) == -1)
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

int	init_value(t_settings *value, int argc, char **argv)
{
	int i;

	i = 0;
	value->num_philo = ft_atoi(argv[1]) * 1000;
	value->time_die = ft_atoi(argv[2]) * 1000;
	value->time_eat = ft_atoi(argv[3]) * 1000;
	value->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc != 6)
		value->num_must_eat = -1;
	else if (argc == 6)
		value->num_must_eat = ft_atoi(argv[5]);
	value->fork = (t_fork *) malloc(sizeof(t_fork) * value->num_philo);
	if (value->fork == NULL)
		return (-1);
	while (i < value->num_philo)
	{
		pthread_mutex_init(&value->fork[i].mutex_t, NULL);
		i++;
	}
	return (0);
}

void *work_philo(void *buf)
{
	
}

int	init_thread(t_settings *settings)
{
	int i;
	t_philo *philo;
	
	i = 0;
	philo =(t_philo *) malloc(sizeof(t_philo) * settings->num_philo);
	if (philo == NULL)
		return (-1);
	while ( i < settings->num_philo)
	{
		
		philo[i].start_time_eat = gettimeofday(&philo[i], NULL);
		pthread_create(&philo[i].thread,NULL,work_philo, (void *) &philo[i]);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_settings value;
	
	value.time_start = gettimeofday(&value, NULL);
	if (parse_value(argc, argv) == -1 && value.time_start == -1)
		return (0);
	init_value(&value, argc, argv);
	init_thread(&value);
	// printf("%d\n", value.num_philo);
	// printf("%d\n", value.time_die);
	// printf("%d\n", value.time_eat);
	// printf("%d\n", value.time_sleep);
	// printf("%d\n", value.num_must_eat);
	return (0);
}