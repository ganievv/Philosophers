/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:12:55 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/20 18:14:22 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%ld %d %s\n",
		((current_time.tv_sec * 1000000 + current_time.tv_usec)
			- (philo->prog_data->start_time.tv_sec * 1000000
				+ philo->prog_data->start_time.tv_usec))
		/ 1000,
		philo->id + 1, message);
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
}
