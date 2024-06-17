/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:04:15 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/17 15:55:20 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char **argv, int argc)
{
	int	i;
	int	y;

	i = 1;
	while (i < argc)
	{
		y = 0;
		while (argv[i][y])
		{
			if (argv[i][y] >= '0' && argv[i][y] <= '9')
				y++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	is_correct_num(char **nums, int size)
{
	if (ft_atoi(nums[1]) <= 0 || ft_atoi(nums[1]) > 200)
		return (0);
	if (ft_atoi(nums[2]) <= 0 || ft_atoi(nums[3]) <= 0
		|| ft_atoi(nums[4]) <= 0)
		return (0);
	if (size == 6)
	{
		if (ft_atoi(nums[5]) < 0)
			return (0);
	}
	return (1);
}

static void	prog_data_init(char **argv, int argc, t_program *data)
{
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->each_philo_must_eat_num = ft_atoi(argv[5]);
	else
		data->each_philo_must_eat_num = -1;
}

int	main(int argc, char **argv)
{
	t_program	data;
	int			error_flag;

	if ((argc == 5 || argc == 6) && is_num(argv, argc)
		&& is_correct_num(argv, argc))
	{
		prog_data_init(argv, argc, &data);
		launch_philos(&data, &error_flag);
		if (error_flag)
			return (1);
		return (0);
	}
	return (1);
}
