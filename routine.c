/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/18 15:40:25 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(useconds_t usec)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000LL
			+ (current.tv_usec - start.tv_usec);
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (true)
	{
		if (philo->id + 1 % 2 != 0)
		{
			pthread_mutex_lock(philo->fork);
		}
	}
	return (NULL);
}
