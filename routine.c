/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/19 16:20:07 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	odd_num_philos(t_philo *philo)
{
	while (true)
	{
		if ((philo->id != philo->prog_data->philo_num - 1)
			&& (philo->id + 1 % 2 != 0))
		{
		}
	}
}

static void	even_num_philos(t_philo *philo)
{
	while (true)
	{
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->prog_data->philo_num % 2 != 0)
		odd_num_philos(philo);
	else
		even_num_philos(philo);
	return (NULL);
}
