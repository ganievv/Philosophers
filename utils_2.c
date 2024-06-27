/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:51:21 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/27 08:58:44 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	activate_threads_and_monitor(t_program *data, int *err_flag)
{
	data->start_time = take_time(MILLISECONDS);
	data->is_ready = 1;
	if (pthread_create(&data->th_monitoring, NULL,
			monitoring, data) != 0)
	{
		data->stop_flag = 1;
		*err_flag = 1;
	}
}
