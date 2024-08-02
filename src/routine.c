/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/02 15:19:18 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_message(philo, "has taken a fork");
}

static void	take_forks_and_eat(t_philo *philo, long time_to_eat_us)
{
	if (philo->id % 2 == 0)
	{
		take_fork(philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(philo->left_fork, philo);
	}
	set_ullong_var(&philo->last_meal_time_mutex, take_time(MILLISECONDS),
		&philo->last_meal_time);
	print_message(philo, "is eating");
	ft_usleep(time_to_eat_us);
	if (philo->must_eat_num != -1)
	{
		philo->times_eaten++;
		if (philo->times_eaten >= philo->must_eat_num)
			set_bool_var(&philo->is_full_mutex, true, &philo->is_full);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	think(t_philo *philo)
{
	unsigned int	to_think;

	to_think = (philo->time_to_eat_us * 2) - philo->time_to_sleep_us;
	ft_usleep(to_think);
}

void	*routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (!get_bool_var(&philo->prog_data->is_ready_mutex,
			&philo->prog_data->is_ready))
		usleep(10);
	if (philo->id % 2 != 0)
		ft_usleep(philo->time_to_eat_us / 2);
	while (!get_bool_var(&philo->prog_data->stop_flag_mutex_prog,
		&philo->prog_data->stop_flag)
		&& !get_bool_var(&philo->is_full_mutex, &philo->is_full))
	{
		take_forks_and_eat(philo, philo->time_to_eat_us);
		print_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep_us);
		print_message(philo, "is thinking");
		if (philo->philo_num % 2 != 0)
			think(philo);
	}
	return (NULL);
}
