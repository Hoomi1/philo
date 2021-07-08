/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:40:08 by cyuuki            #+#    #+#             */
/*   Updated: 2021/07/08 21:25:08 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_settings *settings;

int			get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int pars_str(int argc, char **argv)
{
	int i;
	int j;
	
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_value(int argc, char **argv)
{
	
	if (argc < 5 ||  argc > 6)
	{
		if (argc < 5)
			printf("Few arguments\n");
		else if (argc > 6)
			printf("Many arguments\n");
		return (-1);
	}
	if (pars_str(argc, argv) == -1)
	{
		printf("Arguments are numbers only\n");
		return (-1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("At least once philosophers eat\n");
		return (-1);
	}
	return (0);
}

int	init_value(int argc, char **argv)
{
	int i;

	i = 0;
	settings->num_philo = ft_atoi(argv[1]);
	settings->time_die = ft_atoi(argv[2]) * 1000;
	settings->time_eat = ft_atoi(argv[3]) * 1000;
	settings->time_sleep = ft_atoi(argv[4]) * 1000;
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
		settings->fork[i].index = 0;
		i++;
	}
	return (0);
}

int take_forks(t_philo *philo)
{
	while (1)
	{
		if (settings->fork[philo->num_i].index == 0 && settings->fork[philo->num_i + 1].index == 0)
		{
			pthread_mutex_lock(&(settings->fork[philo->num_i].mutex_t));
			settings->fork[philo->num_i].index = 1;
			printf(" %d %d has taken a fork\n", get_time() - philo->time_life, philo->num_i + 1); // FuncTION
			pthread_mutex_lock(&(settings->fork[philo->num_i + 1].mutex_t));
			settings->fork[philo->num_i + 1].index = 1;
			printf(" %d %d has taken a fork\n", get_time() - philo->time_life, philo->num_i + 1);
			printf(" %d %d is eating \n", get_time() - philo->time_life, philo->num_i + 1);
			philo->start_time_eat = get_time();
			usleep(settings->time_eat);
			if (philo->sum_eat != -1)
				philo->sum_eat++;
			pthread_mutex_unlock(&(settings->fork[philo->num_i + 1].mutex_t));
			pthread_mutex_unlock(&(settings->fork[philo->num_i].mutex_t));
			settings->fork[philo->num_i + 1].index = 0;
			settings->fork[philo->num_i].index = 0;
			//return (0);
		}
		else if (get_time() - philo->start_time_eat > settings->time_die / 1000)
			return (-1);
		else
		{
			// printf("DEADADADAD - %d     %d\n", get_time() - philo->start_time_eat, settings->time_die /1000);
			usleep(100);
		}
		break ; 
	}
	//printf("DEADADADAD - %d     %d\n", get_time() - philo->start_time_eat, settings->time_die /1000);

	return (0);
}

void sleeping(t_philo *philo)
{
	printf(" %d %d is sleeping \n", get_time() - philo->time_life ,philo->num_i + 1);
}

void thinking(t_philo *philo)
{
	printf(" %d %d is is thinking \n", get_time() - philo->time_life, philo->num_i + 1);
	usleep(settings->time_sleep);
}

void *work_philo(void *buf)
{
	t_philo *philo;
	int i;
	
	philo = buf;
	i = 0;
	philo->time_life = get_time();
	while(1)
	{
		if (take_forks(philo) == -1)
		{
			printf("%d %d died", get_time() - philo->time_life, philo->num_i + 1);
			break;
		}
		// if (settings->num_must_eat == philo->sum_eat)
		// {
		// 	break; //free
		// }
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}

int	init_thread()
{
	int i;
	t_philo *philo;
	
	i = 0;
	philo = malloc(sizeof(t_philo) * settings->num_philo);
	if (philo == NULL)
		return (-1);
	while (i < settings->num_philo)
	{
		philo[i].num_i = i;
		//philo[i].start_time_eat = get_time();
		if(pthread_create(&philo[i].thread, NULL, work_philo, &philo[i]) != 0)
			return (-1);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < settings->num_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	settings = (t_settings *) malloc(sizeof(t_settings));
	settings->time_start = get_time();
	if (parse_value(argc, argv) == -1 && settings->time_start == -1)
		return (0);
	init_value(argc, argv);
	init_thread();
	// printf("%d\n", value.num_philo);
	// printf("%d\n", value.time_die);
	// printf("%d\n", value.time_eat);
	// printf("%d\n", value.time_sleep);
	// printf("%d\n", value.num_must_eat);
	return (0);
}