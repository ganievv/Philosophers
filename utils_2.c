/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:18:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/03 13:20:56 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexes_init(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].is_full_mutex, NULL);
		pthread_mutex_init(&data->philos[i].last_meal_time_mutex, NULL);
		pthread_mutex_init(&data->philos[i].stop_flag_mutex, NULL);
	}
	pthread_mutex_init(&data->prog_data_mutex, NULL);
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
	pthread_mutex_destroy(&data->prog_data_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_meal_time_mutex);
		pthread_mutex_destroy(&data->philos[i].is_full_mutex);
		pthread_mutex_destroy(&data->philos[i].stop_flag_mutex);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	stop_all_philos(t_philo *philos, long philo_num)
{
	int	i;

	i = -1;
	while (++i < philo_num)
		set_bool_var(&philos[i].stop_flag_mutex, true, &philos[i].stop_flag);
}
