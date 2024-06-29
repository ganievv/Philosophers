/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/29 13:20:29 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	set_ullong_var(&philo->philo_mutex, take_time(MILLISECONDS),
		&philo->last_meal_time);
	print_message(philo, "is eating");
	ft_usleep(time_to_eat_us);
	increment_long(&philo->philo_mutex, &philo->times_eaten);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	synchronize_philos(t_philo *philo, t_program *prog_data)
{
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->is_ready))
		;
	set_ullong_var(&philo->philo_mutex, take_time(MILLISECONDS),
		&philo->last_meal_time);
}

void	*routine(void *data)
{
	t_philo		*philo;
	t_program	*prog_data;

	philo = (t_philo *)data;
	prog_data = philo->prog_data;
	synchronize_philos(philo, prog_data);
	increment_long(&prog_data->prog_data_mutex, &prog_data->active_threads_num);
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->stop_flag)
		&& !get_bool_var(&philo->philo_mutex, &philo->is_full))
	{
		take_forks_and_eat(philo, philo->time_to_eat_us);
		print_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep_us);
		print_message(philo, "is thinking");
	}
	return (NULL);
}
