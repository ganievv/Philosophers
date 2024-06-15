/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:04:15 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/15 16:51:22 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positiv(char **nums)
{
	int	i;

	i = 1;
	while (i < 6)
	{
		if (ft_atoi(nums[i++]) <= 0)
			return (0);
	}
	return (1);
}

static void	initialize(char **argv, int argc, t_philo *data)
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
	t_philo	data;

	if ((argc == 5 || argc == 6) && is_positiv(argv))
	{
		initialize(argv, argc, &data);
	}
	return (0);
}
