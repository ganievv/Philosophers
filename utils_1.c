/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:33:06 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/29 12:44:36 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	number;
	int		i;
	int		minus;

	i = 0;
	minus = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (minus == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		number = (number * 10) + (str[i++] - '0');
	return (number * minus);
}

unsigned long long	take_time(t_time_units unit)
{
	unsigned long long	time;
	struct timeval		clock;

	if (gettimeofday(&clock, NULL) == -1)
		return (0);
	if (unit == MILLISECONDS)
		time = clock.tv_sec * 1000 + clock.tv_usec / 1000;
	else if (unit == MICROSECONDS)
		time = clock.tv_sec * 1000000 + clock.tv_usec;
	else
		return (0);
	return (time);
}

void	ft_usleep(useconds_t usec)
{
	unsigned long long	start;
	unsigned long long	elapsed;
	unsigned long long	rem;

	elapsed = 0;
	start = take_time(MICROSECONDS);
	while (true)
	{
		elapsed = take_time(MICROSECONDS) - start;
		if (elapsed >= usec)
			break ;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->prog_data->print_mutex);
	if (!get_bool_var(&philo->prog_data->prog_data_mutex,
			&philo->prog_data->stop_flag))
	{
		printf("%lld %d %s\n",
			(take_time(MILLISECONDS) - philo->prog_data->start_time),
			philo->id + 1, message);
	}
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
}

void	increment_long(pthread_mutex_t *mutex, long *var)
{
	pthread_mutex_lock(mutex);
	(*var)++;
	pthread_mutex_unlock(mutex);
}
