/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:42:04 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/11 02:50:33 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings	*g_settings;

static void	*work_philo(void *buf)
{
	t_philo	*philo;
	int		i;

	philo = buf;
	i = 0;
	while (1)
	{
		take_forks(philo, g_settings);
		sleeping(philo, g_settings);
		thinking(philo, g_settings);
	}
	return (NULL);
}

static int	end_philo(t_philo *philo, t_settings *g_settings)
{
	int	i;

	i = 0;
	while (i < g_settings->num_philo)
	{
		if (get_time() - philo->start_time_eat > g_settings->time_die / 1000)
		{
			printf(" %zu ", get_time() - g_settings->time_start);
			printf("%d died \n", philo->num_i + 1);
			g_settings->stop_all_thr = 1;
			pthread_mutex_lock(&g_settings->xz);
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	seting_philo(int i, t_philo *philo, t_settings *g_settings)
{
	philo[i].num_i = i;
	philo[i].l_fork = i;
	philo[i].start_time_eat = g_settings->time_start;
	philo[i].sum_eat = 0;
	philo[i].flag_eat = 0;
	if (i == 0)
		philo[i].r_fork = g_settings->num_philo - 1;
	else
		philo[i].r_fork = (i - 1);
}

static int	init_thread(t_settings *g_settings, t_philo *philo)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * g_settings->num_philo);
	if (philo == NULL)
		return (-1);
	while (i < g_settings->num_philo)
	{
		seting_philo(i, philo, g_settings);
		if (pthread_create(&philo[i].thread, NULL, work_philo, &philo[i]) != 0)
			return (-1);
		usleep(50);
		i++;
	}
	while (g_settings->stop_all_thr != 1)
	{
		usleep(1000);
		i = end_philo(philo, g_settings);
		if (i == -1)
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	g_settings = (t_settings *) malloc(sizeof(t_settings));
	if (parse_value(argc, argv) == -1)
		return (0);
	if (init_value(argc, argv, g_settings, philo) == -1)
		return (0);
	g_settings->time_start = get_time();
	if (g_settings->num_philo > 0)
		init_thread(g_settings, philo);
	destoy_human(philo, g_settings);
	return (0);
}
