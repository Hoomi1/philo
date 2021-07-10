/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:42:04 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/11 00:01:21 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings	*g_settings;

void check_eat(t_philo *philo)
{
	philo->sum_eat++;
	if (philo->sum_eat == g_settings->num_must_eat && philo->flag_eat != 1)
	{
		g_settings->index_eat++;
		philo->flag_eat = 1;
	}
	if (g_settings->index_eat == g_settings->num_philo)
	{
		pthread_mutex_lock(&g_settings->xz);
		g_settings->stop_all_thr = 1;
	}
}

void	eat_fork(t_philo *philo)
{
	pthread_mutex_lock(&g_settings->fork[philo->r_fork].mutex_t);
	g_settings->fork[philo->r_fork].status = 1;
	printf(" %zu %d has taken a fork\n", \
		get_time() - g_settings->time_start, philo->num_i + 1);
	pthread_mutex_lock(&g_settings->fork[philo->l_fork].mutex_t);
	g_settings->fork[philo->l_fork].status = 1;
	printf(" %zu %d has taken a fork\n", \
		get_time() - g_settings->time_start, philo->num_i + 1);
	pthread_mutex_lock(&g_settings->xz);
	pthread_mutex_unlock(&g_settings->xz);
	philo->start_time_eat = get_time();
	printf(" %zu %d is eating \n", \
		get_time() - g_settings->time_start, philo->num_i + 1);
	check_eat(philo);
	usleep(g_settings->time_eat);
	g_settings->fork[philo->l_fork].status = 0;
	g_settings->fork[philo->r_fork].status = 0;
	pthread_mutex_unlock(&(g_settings->fork[philo->r_fork].mutex_t));
	pthread_mutex_unlock(&(g_settings->fork[philo->l_fork].mutex_t));
}

int	take_forks(t_philo *philo, t_settings *g_settings)
{
	while (1)
	{
		if (g_settings->fork[philo->r_fork].status == 0)
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
		- g_settings->time_start, philo->num_i + 1);
	usleep(g_settings->time_sleep);
}

void	thinking(t_philo *philo, t_settings *g_settings)
{
	pthread_mutex_lock(&g_settings->xz);
	pthread_mutex_unlock(&g_settings->xz);
	printf(" %zu %d is is thinking \n", get_time() \
	- g_settings->time_start, philo->num_i + 1);
}

void	*work_philo(void *buf)
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

int	init_thread(t_settings *g_settings, t_philo *philo)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * g_settings->num_philo);
	if (philo == NULL)
		return (-1);
	while (i < g_settings->num_philo)
	{
		philo[i].num_i = i;
		philo[i].l_fork = i;
		philo[i].start_time_eat = g_settings->time_start;
		philo[i].sum_eat = 0;
		philo[i].flag_eat = 0;
		if (i == 0)
		{
			philo[i].r_fork = g_settings->num_philo - 1;
		}
		else
			philo[i].r_fork = (i - 1);
		if (pthread_create(&philo[i].thread, NULL, work_philo, &philo[i]) != 0)
			return (-1);
		usleep(50);
		i++;
	}
	i = 0;
	while (g_settings->stop_all_thr != 1)
	{
		usleep(2000);
		while (i < g_settings->num_philo)
		{
			if (get_time() - philo->start_time_eat > g_settings->time_die / 1000)
			{
				printf(" %zu ", get_time() - g_settings->time_start);
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
	init_value(argc, argv, g_settings, philo);
	g_settings->time_start = get_time();
	if (g_settings->num_philo > 0)
		init_thread(g_settings, philo);
	return (0);
}
