/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:04:15 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/28 10:21:36 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// you should add checking if numbers are not bigger than INT_MAX (done)
// because we have limit as INT_MAX then size of str with number ...
// should be <= 10 (done)

// timestamps should be bigger than 60 milliseconds(ms) (done)
// so you can change just not > 0 but > 60 is valid (done)

//he said that numbers like "      +77$%" should be also legit (done)

// 1e3 == 1×10^3 (done)
// 2.5e-4 == 2.5×10^(−4) (done)

// it is easier to create 'error_exit' function instead of always return
// value to the previous function and so on (but I can't use exit() function)

// you should create handle of errors for mutexes, like that it will be easier
// to find your mistake

//you should move from utils_2.c some functions to a new file

static int	is_num(char **argv)
{
	int	i;
	int	y;
	int	size;

	i = 0;
	while (argv[++i])
	{
		y = 0;
		size = 0;
		while (argv[i][y] == ' ' || (argv[i][y] >= 9 && argv[i][y] <= 13))
			y++;
		if (argv[i][y] == '-' || argv[i][y] == '+')
			y++;
		while (argv[i][y] >= '0' && argv[i][y] <= '9')
		{
			y++;
			size++;
		}
		if (size == 0 || size > 10)
			return (0);
	}
	return (1);
}

static void	prog_data_init(char **argv, int argc, t_program *data)
{
	data->philo_num = ft_atol(argv[1]);
	data->time_to_die_us = ft_atol(argv[2]) * 1e3;
	data->time_to_eat_us = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep_us = ft_atol(argv[4]) * 1e3;
	if (argc == 6)
		data->each_philo_must_eat_num = ft_atol(argv[5]);
	else
		data->each_philo_must_eat_num = -1;
	data->stop_flag = 0;
	data->is_ready = 0;
	data->monitor_start = 0;
}

static int	is_correct_num(t_program *data, int argc)
{
	if (data->philo_num < 1 || data->philo_num > 200)
		return (0);
	if (data->time_to_die_us < 6e4 || data->time_to_eat_us < 6e4
		|| data->time_to_sleep_us < 6e4)
		return (0);
	if (data->time_to_die_us > INT_MAX * 1e3
		|| data->time_to_eat_us > INT_MAX * 1e3
		|| data->time_to_sleep_us > INT_MAX * 1e3)
		return (0);
	if (argc == 6)
	{
		if (data->each_philo_must_eat_num < 0
			|| data->each_philo_must_eat_num > INT_MAX)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	data;

	if ((argc == 5 || argc == 6) && is_num(argv))
	{
		prog_data_init(argv, argc, &data);
		if (!is_correct_num(&data, argc))
			return (1);
		if (launch_philos(&data))
			return (1);
		return (0);
	}
	return (1);
}
