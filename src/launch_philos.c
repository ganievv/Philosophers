/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/01 22:25:36 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	philo_init(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].id = i;
		data->philos[i].times_eaten = 0;
		data->philos[i].prog_data = data;
		data->philos[i].philo_num = data->philo_num;
		data->philos[i].must_eat_num = data->each_philo_must_eat_num;
		data->philos[i].time_to_sleep_us = data->time_to_sleep_us;
		data->philos[i].time_to_eat_us = data->time_to_eat_us;
		data->philos[i].is_full = false;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->philo_num];
		data->philos[i].is_visited = false;
	}
}

static int	all_alloc_init(t_program *data)
{
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
	philo_init(data);
	return (0);
}

static int	handle_edge_cases(t_program *data)
{
	if (data->each_philo_must_eat_num == 0)
		return (1);
	if (data->philo_num == 1)
	{
		handle_one_philo(data);
		return (1);
	}
	return (0);
}

int	launch_philos(t_program *data)
{
	int	i;
	int	err_flag;

	i = -1;
	err_flag = 0;
	if (handle_edge_cases(data))
		return (0);
	if (all_alloc_init(data))
		return (1);
	while ((err_flag != 1) && (++i < data->philo_num))
	{
		if (pthread_create(&data->philos[i].th, NULL,
				routine, &data->philos[i]) != 0)
			err_flag = 1;
	}
	create_monitor(data);
	free_alloc_data(data, &err_flag);
	return (err_flag);
}
