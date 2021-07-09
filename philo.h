/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:14:30 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/09 19:36:34 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
#include <string.h>



typedef struct s_settings
{
	int num_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int num_must_eat;
	struct s_fork *fork;
	pthread_mutex_t xz;
	int time_start;
	int stop_all_thr;

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
	int time_life;
} t_philo;

int	ft_atoi(const char *s);
int	ft_isdigit(int c);
int	parse_value(int argc, char **argv);
int	get_time(void);
int	init_value(int argc, char **argv, t_settings *g_settings);
//void *work_philo(void *buf);

#endif