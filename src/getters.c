/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:12:27 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/28 12:13:42 by sganiev          ###   ########.fr       */
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

unsigned long long	get_ullong_var(pthread_mutex_t *mutex,
	unsigned long long *value)
{
	unsigned long long	buf;

	pthread_mutex_lock(mutex);
	buf = *value;
	pthread_mutex_unlock(mutex);
	return (buf);
}

long	get_long_var(pthread_mutex_t *mutex, long *value)
{
	long	buf;

	pthread_mutex_lock(mutex);
	buf = *value;
	pthread_mutex_unlock(mutex);
	return (buf);
}
