/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/28 10:34:03 by sganiev          ###   ########.fr       */
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
	long		elapsed;
	t_program	*prog_data;

	prog_data = philo->prog_data;
	elapsed = take_time(MILLISECONDS)
		- get_ullong_var(&philo->philo_mutex,
			&philo->last_meal_time);
	if (elapsed >= time_to_die_us / 1000)
	{
		print_message(philo, "died");
		set_bool_var(&prog_data->prog_data_mutex,
			1, &prog_data->stop_flag);
		return (1);
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_program			*prog_data;
	int					i;

	prog_data = (t_program *)data;
	while (!get_bool_var(&prog_data->prog_data_mutex,
			&prog_data->monitor_start))
		;
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->stop_flag))
	{
		i = -1;
		while (++i < prog_data->philo_num)
		{
			if (is_dead(&prog_data->philos[i], prog_data->time_to_die_us))
				break ;
			if (!check_times_eaten(&prog_data->philos[i],
					prog_data->each_philo_must_eat_num))
				break ;
		}
	}
	return (NULL);
}
