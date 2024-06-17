/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/17 15:44:16 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	data = NULL;
	return (NULL);
}

static void	philo_init(t_program *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		philos->id = i;
		philos->times_eaten = 0;
		philos->prog_data = data;
		i++;
	}
}

int	launch_philos(t_program *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (philos == NULL)
		return (1);
	philo_init(data, philos);
	while (++i < data->philo_num)
	{
		if (pthread_create(&philos[i].th, NULL, &routine, &philos[i]))
		{
			free(philos);
			return (1);
		}
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(philos[i++].th, NULL))
		{
			free(philos);
			return (1);
		}
	}
	free(philos);
	return (0);
}
