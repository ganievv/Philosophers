/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:33:06 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/26 09:35:56 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	i;
	int	minus;

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

void	ft_usleep(useconds_t usec)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;
	long long		rem;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (true)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000LL
			+ (current.tv_usec - start.tv_usec);
		if (elapsed >= usec)
			break ;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

void	print_message(t_philo *philo, char *message)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	if (!philo->prog_data->stop_flag)
	{
		printf("%ld %d %s\n",
			((current_time.tv_sec * 1000000 + current_time.tv_usec)
				- (philo->prog_data->start_time.tv_sec * 1000000
					+ philo->prog_data->start_time.tv_usec))
			/ 1000,
			philo->id + 1, message);
	}
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
}
