/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:04:15 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/31 16:33:42 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_nbr(char *nbr)
{
	int	size;

	size = 0;
	while (ft_isspace(*nbr))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
		nbr++;
	if (*nbr == '\0')
		return (0);
	while (*nbr)
	{
		if (!ft_isdigit(*nbr))
			return (0);
		nbr++;
		size++;
	}
	if (size > 10)
		return (0);
	else
		return (1);
}

static int	check_argv(char **argv)
{
	while (*argv)
	{
		if (!is_nbr(*argv))
			return (0);
		argv++;
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
	data->stop_flag = false;
	data->is_ready = false;
	data->active_threads_num = 0;
}

static int	is_correct_num(t_program *data, int argc)
{
	if (data->philo_num < 1 || data->philo_num > 200)
		return (0);
	if (data->time_to_die_us <= 0 || data->time_to_eat_us <= 0
		|| data->time_to_sleep_us <= 0)
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

	if ((argc == 5 || argc == 6) && check_argv(argv + 1))
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
