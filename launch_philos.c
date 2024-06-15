/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/15 20:47:11 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
}

int	launch_philos(t_program *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (data->philos == NULL)
		return (1);
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i++].th, NULL, &routine, data))
		{
			free_struct();
			return (1);
		}
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->philos[i++].th, NULL))
			return (1);
	}
	return (0);
}
