/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/20 16:22:04 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_and_starttime_mutex_init(t_program *data)
{
	unsigned int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

static void	set_forks(t_program *data, int i)
{
	int	right_fork_index;

	if (i == 0)
		right_fork_index = data->philo_num - 1;
	else
		right_fork_index = i - 1;
	data->philos[i].left_fork = &data->forks[i];
	data->philos[i].right_fork = &data->forks[right_fork_index];
}

static int	philo_and_fork_init(t_program *data)
{
	unsigned int	i;

	i = 0;
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
	forks_and_starttime_mutex_init(data);
	data->stop_flag = 0;
	while (i < data->philo_num)
	{
		data->philos[i].id = i;
		data->philos[i].times_eaten = 0;
		data->philos[i].prog_data = data;
		set_forks(data, i);
		i++;
	}
	return (0);
}

static void	free_alloc_data(t_program *data)
{
	unsigned int	i;

	i = -1;
	pthread_mutex_destroy(&data->print_mutex);
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i]);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

int	launch_philos(t_program *data)
{
	unsigned int	i;
	int				err_flag;

	i = -1;
	err_flag = 0;
	if (philo_and_fork_init(data))
		return (1);
	gettimeofday(&data->start_time, NULL);
	while ((err_flag != 1) && (++i < data->philo_num))
	{
		if (pthread_create(&data->philos[i].th, NULL,
				&routine, &data->philos[i]) != 0)
			err_flag = 1;
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philos[i].th, NULL) != 0)
			err_flag = 1;
	}
	free_alloc_data(data);
	return (err_flag);
}
