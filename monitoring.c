/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/27 16:47:18 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Maybe when you check last_meal_time it is not already
// appropriate value and because of that philos are dying 

static int	check_times_eaten(t_philo *philo, long must_eat_num)
{
	if (must_eat_num == -1)
		return (1);
	if (get_long_var(&philo->philo_mutex, &philo->times_eaten) < must_eat_num)
		return (1);
	else
	{
		set_bool_var(&philo->prog_data->prog_data_mutex,
			1, &philo->prog_data->stop_flag);
		return (0);
	}
}

static int	is_dead(t_philo *philo, long time_to_die_us)
{
	unsigned long long	elapsed;
	t_program			*prog_data;

	prog_data = philo->prog_data;
	elapsed = take_time(MICROSECONDS)
		- get_ullong_var(&philo->philo_mutex,
			&philo->last_meal_time);
	if (elapsed >= (unsigned long long)time_to_die_us)
	{
		print_message(philo, "died");
		set_bool_var(&prog_data->prog_data_mutex,
			1, &prog_data->stop_flag);
		return (1);
	}
	return (0);
}

static void	initialize(t_program *prog_data, long *time_to_die_us,
	long *philo_num, long *each_philo_must_eat_num)
{
	*time_to_die_us = get_long_var(&prog_data->prog_data_mutex,
			&prog_data->time_to_die_us);
	*philo_num = get_long_var(&prog_data->prog_data_mutex,
			&prog_data->philo_num);
	*each_philo_must_eat_num = get_long_var(&prog_data->prog_data_mutex,
			&prog_data->each_philo_must_eat_num);
}

void	*monitoring(void *data)
{
	t_program			*prog_data;
	int					i;
	long				time_to_die_us;
	long				philo_num;
	long				must_eat_num;

	prog_data = (t_program *)data;
	initialize(prog_data, &time_to_die_us, &philo_num, &must_eat_num);
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->stop_flag))
	{
		i = -1;
		while (++i < philo_num)
		{
			if (is_dead(&prog_data->philos[i], time_to_die_us))
				break ;
			if (!check_times_eaten(&prog_data->philos[i], must_eat_num))
				break ;
		}
	}
	return (NULL);
}
