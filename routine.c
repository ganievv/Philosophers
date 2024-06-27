/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/27 16:36:54 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// what should be first in these lines ???
// gettimeofday(&philo->last_meal_time, NULL);
// or ft_usleep(philo->prog_data->time_to_eat);

// maybe the problem is in your ft_usleep ???

// what should I unlock first and second ?

// what if each_philo_must_eat == 0 ???
// what if philo_num == 1 ???

// if variable has only 0 or 1 than it is better to use bool type

// you should protect shared variables with mutexes even
// if it is only for reading

//you should add to each philo time to sleep and eat variables

static void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_message(philo, "has taken a fork");
}

static void	forks_unlocking(t_philo *philo, int is_order_left)
{
	if (is_order_left)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static void	take_forks_and_eat(t_philo *philo, long time_to_eat_us)
{
	int	is_order_left;

	if (philo->id % 2 == 0)
	{
		take_fork(philo->left_fork, philo);
		take_fork(philo->right_fork, philo);
		is_order_left = 1;
	}
	else
	{
		take_fork(philo->right_fork, philo);
		take_fork(philo->left_fork, philo);
		is_order_left = 0;
	}
	print_message(philo, "is eating");
	set_ullong_var(&philo->philo_mutex, take_time(MILLISECONDS),
		&philo->last_meal_time);
	set_long_var(&philo->philo_mutex,
		get_long_var(&philo->philo_mutex, &philo->times_eaten) + 1,
		&philo->times_eaten);
	ft_usleep(time_to_eat_us);
	forks_unlocking(philo, is_order_left);
}

static int	synchronize_philos(t_philo *philo)
{
	t_program	*prog_data;

	prog_data = philo->prog_data;
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->is_ready))
		;
	set_ullong_var(&philo->philo_mutex, take_time(MILLISECONDS),
		&philo->last_meal_time);
	return (1);
}

void	*routine(void *data)
{
	t_philo		*philo;
	t_program	*prog_data;
	long		time_to_sleep_us;
	long		time_to_eat_us;

	philo = (t_philo *)data;
	prog_data = philo->prog_data;
	time_to_sleep_us = get_long_var(&prog_data->prog_data_mutex,
			&prog_data->time_to_sleep_us);
	time_to_eat_us = get_long_var(&prog_data->prog_data_mutex,
			&prog_data->time_to_eat_us);
	if (!synchronize_philos(philo))
		return (NULL);
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->stop_flag))
	{
		take_forks_and_eat(philo, time_to_eat_us);
		print_message(philo, "is sleeping");
		ft_usleep(time_to_sleep_us);
		print_message(philo, "is thinking");
	}
	return (NULL);
}
