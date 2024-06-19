/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:38:35 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/19 19:39:01 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%lld %d is thinking\n",
		(current_time.tv_sec - philo->prog_data->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->prog_data->start_time.tv_usec) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
}
