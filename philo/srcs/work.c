/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 02:08:12 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/15 16:09:10 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_eat(t_philo *philo, t_settings *g_settings)
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

static void	eat_fork(t_philo *philo, t_settings *g_settings)
{	
	pthread_mutex_lock(&g_settings->fork[philo->r_fork].mutex_t);
	g_settings->fork[philo->r_fork].status = 1;
	write_philo(1, g_settings, philo);
	pthread_mutex_lock(&g_settings->fork[philo->l_fork].mutex_t);
	g_settings->fork[philo->l_fork].status = 1;
	write_philo(1, g_settings, philo);
	pthread_mutex_lock(&g_settings->xz);
	pthread_mutex_unlock(&g_settings->xz);
	philo->start_time_eat = get_time();
	write_philo(2, g_settings, philo);
	if (g_settings->num_must_eat != -1)
		check_eat(philo, g_settings);
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
			eat_fork(philo, g_settings);
			break ;
		}
		else
			usleep(100);
	}
	return (0);
}

void	sleeping(t_philo *philo, t_settings *g_settings)
{
	write_philo(3, g_settings, philo);
	usleep(g_settings->time_sleep);
}

void	thinking(t_philo *philo, t_settings *g_settings)
{
	write_philo(4, g_settings, philo);
}
