/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activate_th_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:14:42 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/01 16:07:44 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	activate_threads_and_monitor(t_program *data, int *err_flag)
{
	if (*err_flag)
		return ;
	set_ullong_var(&data->prog_data_mutex, take_time(MILLISECONDS),
		&data->start_time);
	set_bool_var(&data->prog_data_mutex, 1, &data->is_ready);
	if (pthread_create(&data->th_monitoring, NULL,
			monitoring, data) != 0)
	{
		set_bool_var(&data->prog_data_mutex, 1, &data->stop_flag);
		*err_flag = 1;
	}
}
