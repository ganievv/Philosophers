/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks_and_eat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:19:21 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/19 17:58:49 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(pthread_mutex_t *fork, pthread_mutex_t *print_mutex,
int id, struct timeval *start_time)
{
	struct timeval	current_time;

	pthread_mutex_lock(fork);
	pthread_mutex_lock(print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%lld %d has taken a fork\n",
		(current_time.tv_sec - start_time->tv_sec) * 1000
		+ (current_time.tv_usec - start_time->tv_usec) / 1000,
		id + 1);
	pthread_mutex_unlock(print_mutex);
}

static void	eat(int id, pthread_mutex_t *print_mutex,
struct timeval *start_time, int time_to_eat)
{
	struct timeval	current_time;

	pthread_mutex_lock(print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%lld %d is eating\n",
		(current_time.tv_sec - start_time->tv_sec) * 1000
		+ (current_time.tv_usec - start_time->tv_usec) / 1000,
		id + 1);
	ft_usleep(time_to_eat * 1000);
	pthread_mutex_unlock(print_mutex);
}

void	take_forks_and_eat(t_philo *philo)
{
	struct timeval	current_time;

	take_fork(philo->left_fork, &philo->prog_data->print_mutex,
		philo->id, &philo->prog_data->start_time);
	take_fork(philo->right_fork, &philo->prog_data->print_mutex,
		philo->id, &philo->prog_data->start_time);
	eat(philo->id, &philo->prog_data->print_mutex,
		&philo->prog_data->start_time, philo->prog_data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
