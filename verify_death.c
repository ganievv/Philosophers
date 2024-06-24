/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/24 13:20:13 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	verify_death(t_program *data)
{
	struct timeval		current_time;
	unsigned long long	elapsed;
	unsigned int		i;

	i = 0;
	while (i < data->philo_num)
	{
		gettimeofday(&current_time, NULL);
		elapsed = (current_time.tv_sec * 1000000 + current_time.tv_usec)
			- (data->philos[i].last_meal_time.tv_sec * 1000000
				+ data->philos[i].last_meal_time.tv_usec);
		if (elapsed >= data->time_to_die)
		{
			data->stop_flag = 1;
			print_message(&data->philos[i], "died");
			return ;
		}
		if (++i >= data->philo_num)
			i = 0;
	}
}
