/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/24 13:26:48 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_message(philo, "has taken a fork");
}

static void	take_forks_and_eat(t_philo *philo)
{
	if ((philo->id + 1) % 2 != 0)
	{
		take_fork(philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(philo->left_fork, philo);
	}
	print_message(philo, "is eating");
	ft_usleep(philo->prog_data->time_to_eat);
	gettimeofday(&philo->last_meal_time, NULL);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	check_times_eaten(t_philo *philo)
{
	if (philo->prog_data->each_philo_must_eat_num == -1)
		return (1);
	if (philo->times_eaten < philo->prog_data->each_philo_must_eat_num)
		return (1);
	else
		return (0);
}

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	gettimeofday(&philo->last_meal_time, NULL);
	while (!philo->prog_data->stop_flag && check_times_eaten(philo))
	{
		take_forks_and_eat(philo);
		print_message(philo, "is sleeping");
		ft_usleep(philo->prog_data->time_to_sleep);
		print_message(philo, "is thinking");
	}
	return (NULL);
}
