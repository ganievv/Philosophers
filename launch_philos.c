/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/28 09:05:14 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutexes_init(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].philo_mutex, NULL);
	}
	pthread_mutex_init(&data->prog_data_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

static void	set_fork(t_program *data, int i)
{
	int	left_fork_index;

	left_fork_index = (i + 1) % data->philo_num;
	data->philos[i].right_fork = &data->forks[i];
	data->philos[i].left_fork = &data->forks[left_fork_index];
}

static int	philo_and_fork_init(t_program *data)
{
	int	i;

	i = -1;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_num);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	mutexes_init(data);
	while (++i < data->philo_num)
	{
		data->philos[i].id = i;
		data->philos[i].times_eaten = 0;
		data->philos[i].prog_data = data;
		data->philos[i].time_to_sleep_us = data->time_to_sleep_us;
		data->philos[i].time_to_eat_us = data->time_to_eat_us;
		set_fork(data, i);
	}
	return (0);
}

static void	free_alloc_data(t_program *data, int *err_flag)
{
	int	i;

	i = -1;
	if (pthread_join(data->th_monitoring, NULL) != 0)
		*err_flag = 1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philos[i].th, NULL) != 0)
			*err_flag = 1;
	}
	i = -1;
	pthread_mutex_destroy(&data->prog_data_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

int	launch_philos(t_program *data)
{
	int	i;
	int	err_flag;

	i = -1;
	err_flag = 0;
	if (philo_and_fork_init(data))
		return (1);
	while ((err_flag != 1) && (++i < data->philo_num))
	{
		if (pthread_create(&data->philos[i].th, NULL,
				routine, &data->philos[i]) != 0)
			err_flag = 1;
	}
	activate_threads_and_monitor(data, &err_flag);
	free_alloc_data(data, &err_flag);
	return (err_flag);
}
