/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/24 18:38:17 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*verify_death(void *data)
{
	t_program			*prog_data;
	struct timeval		current_time;
	unsigned long long	elapsed;
	int					i;

	prog_data = (t_program *)data;
	while (!prog_data->stop_flag)
	{
		i = -1;
		while (++i < prog_data->philo_num)
		{
			gettimeofday(&current_time, NULL);
			elapsed = (current_time.tv_sec * 1000000 + current_time.tv_usec)
				- (prog_data->philos[i].last_meal_time.tv_sec * 1000000
					+ prog_data->philos[i].last_meal_time.tv_usec);
			if (elapsed >= prog_data->time_to_die)
			{
				print_message(&prog_data->philos[i], "died");
				prog_data->stop_flag = 1;
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}
