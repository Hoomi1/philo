/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 03:02:14 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/15 15:55:10 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex_t;
	int				status;
}					t_fork;

typedef struct s_philo
{
	int			num_i;
	pthread_t	thread;
	size_t		start_time_eat;
	int			sum_eat;
	int			l_fork;
	int			r_fork;
	int			flag_eat;
}				t_philo;

typedef struct s_settings
{
	int				num_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				num_must_eat;
	t_fork			*fork;
	pthread_mutex_t	xz;
	size_t			time_start;
	int				stop_all_thr;
	int				index_eat;

}					t_settings;

int		ft_atoi(const char *s);
int		ft_isdigit(int c);
int		parse_value(int argc, char **argv);
size_t	get_time(void);
int		init_value(int argc, char **argv \
, t_settings *g_settings);
int		take_forks(t_philo *philo, t_settings *g_settings);
void	sleeping(t_philo *philo, t_settings *g_settings);
void	thinking(t_philo *philo, t_settings *g_settings);
int		destoy_human(t_philo *philo, t_settings *g_settings);
void	write_philo(int index, t_settings *settings, t_philo *philo);
int		my_destroy_mutex(t_settings *g_settings);

#endif