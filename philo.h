/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:14:30 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/06 20:48:22 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_settings
{
	int num_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int num_must_eat;
	struct s_fork *fork;
	int time_start;
} t_settings;

typedef struct s_fork
{
	pthread_mutex_t mutex_t;
	int index;
} t_fork;

typedef struct s_philo
{
	int num_i;
	pthread_t thread;
	int start_time_eat;
	int sum_eat;
} t_philo;

int	ft_atoi(const char *s);
int	ft_isdigit(int c);

#endif