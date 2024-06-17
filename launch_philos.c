/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/17 16:32:27 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_program *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		philos[i].id = i;
		philos[i].times_eaten = 0;
		philos[i].prog_data = data;
		i++;
	}
}

void	launch_philos(t_program *data, int	*error_flag)
{
	int	i;

	i = -1;
	philo_init(data, data->philos);
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
