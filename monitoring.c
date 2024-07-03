/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/03 11:53:29 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_times_eaten(t_philo *philo, long must_eat_num, long philo_num)
{
	static int	full_philos_num = 0;

	if (must_eat_num == -1)
		return (1);
	if (!philo->is_visited
		&& get_bool_var(&philo->is_full_mutex, &philo->is_full) == true)
	{
		philo->is_visited = true;
		full_philos_num++;
		if (full_philos_num >= philo_num)
		{
			set_bool_var(&philo->prog_data->prog_data_mutex,
				true, &philo->prog_data->stop_flag);
			return (0);
		}
	}
	return (1);
}

static int	is_dead(t_philo *philo, long time_to_die_us, int philo_num)
{
	long		elapsed;
	t_program	*prog_data;
	int			i;

	i = -1;
	prog_data = philo->prog_data;
	elapsed = take_time(MILLISECONDS)
		- get_ullong_var(&philo->last_meal_time_mutex, &philo->last_meal_time);
	if (elapsed >= time_to_die_us / 1000)
	{
		if (!get_bool_var(&philo->is_full_mutex, &philo->is_full))
		{
			print_message(philo, "died");
			set_bool_var(&prog_data->prog_data_mutex, 1, &prog_data->stop_flag);
			while (++i < philo_num)
				set_bool_var(&philo->stop_flag_mutex, true, &philo->stop_flag);
			return (1);
		}
	}
	return (0);
}

static void	init_monitor_vars(t_program *prog_data, long *philo_num,
	long *time_to_die, long *must_eat)
{
	pthread_mutex_lock(&prog_data->prog_data_mutex);
	*philo_num = prog_data->philo_num;
	*time_to_die = prog_data->time_to_die_us;
	*must_eat = prog_data->each_philo_must_eat_num;
	pthread_mutex_unlock(&prog_data->prog_data_mutex);
}

void	*monitoring(void *data)
{
	t_program			*prog_data;
	int					i;
	long				philo_num;
	long				time_to_die;
	long				must_eat;

	prog_data = (t_program *)data;
	init_monitor_vars(prog_data, &philo_num, &time_to_die, &must_eat);
	ft_usleep(time_to_die / 3);
	while (!get_bool_var(&prog_data->prog_data_mutex, &prog_data->stop_flag))
	{
		i = -1;
		while (++i < philo_num)
		{
			if (is_dead(&prog_data->philos[i], time_to_die, philo_num))
				break ;
			if (!check_times_eaten(&prog_data->philos[i], must_eat, philo_num))
				break ;
		}
	}
	return (NULL);
}

void	create_monitor(t_program *data, int *err_flag)
{
	int	i;

	i = -1;
	if (*err_flag)
		return ;
	if (pthread_create(&data->th_monitoring, NULL,
			monitoring, data) != 0)
	{
		set_bool_var(&data->prog_data_mutex, 1, &data->stop_flag);
		while (++i < data->philo_num)
			set_bool_var(&data->philos[i].stop_flag_mutex,
				true, &data->philos[i].stop_flag);
		*err_flag = 1;
	}
}
