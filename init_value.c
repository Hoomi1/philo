/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 19:20:07 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/11 00:05:57 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_value(int argc, char **argv, t_settings *settings, t_philo *philo)
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
		pthread_mutex_init(&settings->fork[i].mutex_t, NULL);
		settings->fork[i].status = 0;
		i++;
	}
	return (0);
}
