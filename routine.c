/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/18 20:21:27 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if (philo->id + 1 % 2 != 0)

static void	take_forks_and_eat(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%lld %d has taken a fork\n",
		(current_time.tv_sec - philo->prog_data->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->prog_data->start_time.tv_usec) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%lld %d has taken a fork\n",
		(current_time.tv_sec - philo->prog_data->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->prog_data->start_time.tv_usec) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
	pthread_mutex_lock(&philo->prog_data->print_mutex);
	gettimeofday(&current_time, NULL);
	printf("%lld %d is eating\n",
		(current_time.tv_sec - philo->prog_data->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->prog_data->start_time.tv_usec) / 1000,
		philo->id + 1);
	ft_usleep(philo->prog_data->time_to_eat);
	pthread_mutex_unlock(&philo->prog_data->print_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	odd_num_philos(t_philo *philo)
{
	while (true)
	{
		if ((philo->id != philo->prog_data->philo_num - 1)
			&& (philo->id + 1 % 2 != 0))
		{
		}
	}
}

static void	even_num_philos(t_philo *philo)
{
	while (true)
	{
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->prog_data->philo_num % 2 != 0)
		odd_num_philos(philo);
	else
		even_num_philos(philo);
	return (NULL);
}
