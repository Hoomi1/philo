/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:42:04 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/10 19:14:27 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings	*g_settings;

void	eat_fork(t_philo *philo)
{
	pthread_mutex_lock(&(g_settings->fork[philo->num_i].mutex_t));
	g_settings->fork[philo->num_i].index = 1;
	printf(" %zu %d has taken a fork\n", \
		get_time() - philo->time_life, philo->num_i + 1);
	pthread_mutex_lock(&(g_settings->fork[philo->num_i + 1].mutex_t));
	g_settings->fork[philo->num_i + 1].index = 1;
	printf(" %zu %d has taken a fork\n", \
		get_time() - philo->time_life, philo->num_i + 1);
	pthread_mutex_lock(&g_settings->xz);
	pthread_mutex_unlock(&g_settings->xz);
	philo->start_time_eat = get_time();
	printf(" %zu %d is eating \n", \
	get_time() - philo->time_life, philo->num_i + 1);
	usleep(g_settings->time_eat);
	if (philo->sum_eat != -1)
		philo->sum_eat++;
	pthread_mutex_unlock(&(g_settings->fork[philo->num_i + 1].mutex_t));
	pthread_mutex_unlock(&(g_settings->fork[philo->num_i].mutex_t));
	g_settings->fork[philo->num_i + 1].index = 0;
	g_settings->fork[philo->num_i].index = 0;
}

int	take_forks(t_philo *philo, t_settings *g_settings)
{
	while (g_settings->stop_all_thr != 1)
	{
		if (philo->num_i != g_settings->num_philo - 1 && \
			g_settings->fork[philo->num_i].index == 0 && \
			g_settings->fork[philo->num_i + 1].index == 0)
		{
			eat_fork(philo);
			break ;
		}
		else if (philo->num_i == g_settings->num_philo - 1 && \
		g_settings->fork[philo->num_i].index == 0 && \
		g_settings->fork[0].index == 0)
		{
			eat_fork(philo);
			break ;
		}
		else
			usleep(100);
	}
	return (0);
}

void	sleeping(t_philo *philo, t_settings *g_settings)
{
	pthread_mutex_lock(&g_settings->xz);
	pthread_mutex_unlock(&g_settings->xz);
	printf(" %zu %d is sleeping \n", get_time() \
		- philo->time_life, philo->num_i + 1);
	usleep(g_settings->time_sleep);
}

void	thinking(t_philo *philo, t_settings *g_settings)
{
	pthread_mutex_lock(&g_settings->xz);
	pthread_mutex_unlock(&g_settings->xz);
	printf(" %zu %d is is thinking \n", get_time() \
	- philo->time_life, philo->num_i + 1);
}

void	*work_philo(void *buf)
{
	t_philo	*philo;
	int		i;

	philo = buf;
	i = 0;
	philo->time_life = get_time();
	while (g_settings->stop_all_thr != 1)
	{
		take_forks(philo, g_settings);
		sleeping(philo, g_settings);
		thinking(philo, g_settings);
	}
	return (NULL);
}

int	init_thread(t_settings *g_settings, t_philo *philo)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * g_settings->num_philo);
	if (philo == NULL)
		return (-1);
	philo->time_life = get_time();
	while (i < g_settings->num_philo)
	{
		philo[i].num_i = i;
		if (pthread_create(&philo[i].thread, NULL, work_philo, &philo[i]) != 0)
			return (-1);
		usleep(50);
		i++;
	}
	i = 0;
	while (g_settings->stop_all_thr != 1)
	{
		while (i < g_settings->num_philo)
		{
			if (get_time() - philo->start_time_eat \
				> g_settings->time_die / 1000)
			{
				printf(" %zu ", get_time() - philo->time_life);
				printf("%d died \n", philo->num_i + 1);
				g_settings->stop_all_thr = 1;
				pthread_mutex_lock(&g_settings->xz);
				break ;
			}
			i++;
		}
		i = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	g_settings = (t_settings *) malloc(sizeof(t_settings));
	if (parse_value(argc, argv) == -1)
		return (0);
	init_value(argc, argv, g_settings);
	if (g_settings->num_philo > 0)
		init_thread(g_settings, philo);
	return (0);
}
