/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:40:08 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/09 19:45:16 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings	*g_settings;

void	eat_fork(t_philo *philo)
{
	pthread_mutex_lock(&(g_settings->fork[philo->num_i].mutex_t));
	g_settings->fork[philo->num_i].index = 1;
	printf(" %d %d has taken a fork\n", \
	get_time() - philo->time_life, philo->num_i + 1);
	pthread_mutex_lock(&(g_settings->fork[philo->num_i + 1].mutex_t));
	g_settings->fork[philo->num_i + 1].index = 1;
	printf(" %d %d has taken a fork\n", \
	get_time() - philo->time_life, philo->num_i + 1);
	printf(" %d %d is eating \n", \
	get_time() - philo->time_life, philo->num_i + 1);
	philo->start_time_eat = get_time();
	usleep(g_settings->time_eat);
	if (philo->sum_eat != -1)
		philo->sum_eat++;
	pthread_mutex_unlock(&(g_settings->fork[philo->num_i + 1].mutex_t));
	pthread_mutex_unlock(&(g_settings->fork[philo->num_i].mutex_t));
	g_settings->fork[philo->num_i + 1].index = 0;
	g_settings->fork[philo->num_i].index = 0;
}

int	take_forks(t_philo *philo)
{
	while (1)
	{
		if (get_time() - philo->start_time_eat > g_settings->time_die / 1000)
			return (-1);
		if (g_settings->fork[philo->num_i].index == 0 && g_settings->fork[philo->num_i + 1].index == 0 \
		&& g_settings->stop_all_thr != 1)
		{
			eat_fork(philo);
			break ;
		}
		else
			usleep(100);
	}
	return (0);
}

void	sleeping(t_philo *philo)
{
	if (g_settings->stop_all_thr != 1)
	{
		pthread_mutex_lock(&g_settings->xz);
		printf(" %d %d is sleeping \n", \
		get_time() - philo->time_life, philo->num_i + 1);
		usleep(g_settings->time_sleep);
		pthread_mutex_unlock(&g_settings->xz);
	}
}

void	thinking(t_philo *philo)
{
	if (g_settings->stop_all_thr != 1)
	{
		pthread_mutex_lock(&g_settings->xz);
		printf(" %d %d is is thinking \n", \
		get_time() - philo->time_life, philo->num_i + 1);
		pthread_mutex_unlock(&g_settings->xz);
	}
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
		if (take_forks(philo) == -1 && g_settings->stop_all_thr != 1)
		{
			g_settings->stop_all_thr = 1;
			printf(" %d %d died \n", \
			get_time() - philo->time_life, philo->num_i + 1);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	destroy_thr(t_philo *philo, t_settings *g_settings)
{
	int	i;

	i = 0;
	if (g_settings->stop_all_thr == 1)
	{
		while (i < g_settings->num_philo)
			pthread_detach(philo[i++].thread);
		i = 0;
		while (i < g_settings->num_philo)
		{
			pthread_mutex_destroy(&g_settings->fork[i++].mutex_t);
		}
		pthread_mutex_destroy(&g_settings->xz);
	}
}

int	init_thread(t_settings *g_settings)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * g_settings->num_philo);
	if (philo == NULL)
		return (-1);
	while (i < g_settings->num_philo)
	{
		philo[i].num_i = i;
		if (pthread_create(&philo[i].thread, NULL, work_philo, &philo[i]) != 0)
			return (-1);
		usleep(50);
		destroy_thr(philo, g_settings);
		i++;
	}
	i = 0;
	while (i < g_settings->num_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	g_settings = (t_settings *) malloc(sizeof(t_settings));
	g_settings->time_start = get_time();
	if (parse_value(argc, argv) == -1 && g_settings->time_start == -1)
		return (0);
	init_value(argc, argv, g_settings);
	init_thread(g_settings);
	return (0);
}
