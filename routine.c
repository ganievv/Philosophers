/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/25 17:45:46 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// what should be first in these lines ???
// gettimeofday(&philo->last_meal_time, NULL);
// or ft_usleep(philo->prog_data->time_to_eat);

// maybe the problem is in your ft_usleep ???

// what should I unlock first and second ?

static void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_message(philo, "has taken a fork");
}

static void	mutex_unlocking(t_philo *philo, int is_order_left)
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

static void	take_forks_and_eat(t_philo *philo)
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
	gettimeofday(&philo->last_meal_time, NULL);
	ft_usleep(philo->prog_data->time_to_eat);
	philo->times_eaten++;
	mutex_unlocking(philo, is_order_left);
}

static int	synchronize_philos(t_philo *philo)
{
	t_program	*prog_data;

	prog_data = philo->prog_data;
	if (philo->id == prog_data->philo_num - 1)
	{
		gettimeofday(&prog_data->start_time, NULL);
		prog_data->is_ready = 1;
		if (pthread_create(&prog_data->th_monitoring, NULL,
				monitoring, prog_data) != 0)
		{
			philo->prog_data->stop_flag = 1;
			return (0);
		}
	}
	while (!prog_data->is_ready)
		;
	gettimeofday(&philo->last_meal_time, NULL);
	return (1);
}

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	if (!synchronize_philos(philo))
		return (NULL);
	while (!philo->prog_data->stop_flag)
	{
		take_forks_and_eat(philo);
		print_message(philo, "is sleeping");
		ft_usleep(philo->prog_data->time_to_sleep);
		print_message(philo, "is thinking");
	}
	return (NULL);
}
