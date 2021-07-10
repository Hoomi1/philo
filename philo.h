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
	size_t time_die;
	size_t time_eat;
	size_t time_sleep;
	int num_must_eat;
	struct s_fork *fork;
	pthread_mutex_t xz;
	size_t time_start;
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
	size_t start_time_eat;
	int sum_eat;
	size_t time_life;
	int l_fork;
	int r_fork;
} t_philo;

int	ft_atoi(const char *s);
int	ft_isdigit(int c);
int	parse_value(int argc, char **argv);
size_t	get_time(void);
int	init_value(int argc, char **argv, t_settings *g_settings);
//void *work_philo(void *buf);

#endif