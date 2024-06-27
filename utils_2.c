/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 08:51:21 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/27 16:26:09 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool_var(pthread_mutex_t *mutex, bool *value)
{
	bool	buf;

	pthread_mutex_lock(mutex);
	buf = *value;
	pthread_mutex_unlock(mutex);
	return (buf);
}

void	set_bool_var(pthread_mutex_t *mutex, bool value, bool *dst)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

unsigned long long	get_ullong_var(pthread_mutex_t *mutex,
	unsigned long long *value)
{
	unsigned long long	buf;

	pthread_mutex_lock(mutex);
	buf = *value;
	pthread_mutex_unlock(mutex);
	return (buf);
}

void	set_ullong_var(pthread_mutex_t *mutex,
	unsigned long long value, unsigned long long *dst)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

long	get_long_var(pthread_mutex_t *mutex, long *value)
{
	long	buf;

	pthread_mutex_lock(mutex);
	buf = *value;
	pthread_mutex_unlock(mutex);
	return (buf);
}

void	set_long_var(pthread_mutex_t *mutex, long value, long *dst)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

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
