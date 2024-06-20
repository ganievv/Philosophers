/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:33:05 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/20 16:34:07 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%ld %d died\n",
		((current_time.tv_sec * 1000000 + current_time.tv_usec)
			- (philo->prog_data->start_time.tv_sec * 1000000
				+ philo->prog_data->start_time.tv_usec))
		/ 1000,
		philo->id + 1);
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
}
