/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/18 16:26:58 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_fork_init(t_program *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_num);
	if (!data->philos || !data->forks)
		return (1);
	while (i < data->philo_num)
	{
		data->philos[i].id = i;
		data->philos[i].times_eaten = 0;
		data->philos[i].prog_data = data;
		i++;
	}
	return (0);
}

void	launch_philos(t_program *data, int	*error_flag)
{
	int	i;

	i = -1;
	philo_fork_init(data);
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].th, NULL,
				&routine, &data->philos[i]))
			*error_flag = 1;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->philos[i++].th, NULL))
			*error_flag = 1;
	}
	*error_flag = 0;
}
