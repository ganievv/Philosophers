/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:06:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/17 15:59:11 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	launch_philos(t_program *data, int	*error_flag)
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
			*error_flag = 1;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(philos[i++].th, NULL))
			*error_flag = 1;
	}
	free(philos);
	*error_flag = 0;
}
