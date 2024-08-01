/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:18:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/01 20:12:35 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	mutexes_init(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].is_full_mutex, NULL);
		pthread_mutex_init(&data->philos[i].last_meal_time_mutex, NULL);
	}
	pthread_mutex_init(&data->is_ready_mutex, NULL);
	pthread_mutex_init(&data->stop_flag_mutex_prog, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

void	free_alloc_data(t_program *data, int *err_flag)
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
	pthread_mutex_destroy(&data->is_ready_mutex);
	pthread_mutex_destroy(&data->stop_flag_mutex_prog);
	pthread_mutex_destroy(&data->print_mutex);
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_meal_time_mutex);
		pthread_mutex_destroy(&data->philos[i].is_full_mutex);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
