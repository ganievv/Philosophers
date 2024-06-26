/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/26 17:03:06 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Maybe when you check last_meal_time it is not already
// appropriate value and because of that philos are dying 

static int	check_times_eaten(int each_philo_must_eat_num, int times_eaten,
	bool *stop_flag)
{
	if (each_philo_must_eat_num == -1)
		return (1);
	if (times_eaten < each_philo_must_eat_num)
		return (1);
	else
	{
		*stop_flag = 1;
		return (0);
	}
}

static int	is_dead(t_philo *philos, int index)
{
	unsigned long long	elapsed;

	elapsed = take_time(MICROSECONDS) - philos[index].last_meal_time;
	if (elapsed >= (unsigned long long)philos->prog_data->time_to_die_us)
	{
		print_message(&philos[index], "died");
		philos->prog_data->stop_flag = 1;
		return (1);
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_program			*prog_data;
	int					i;

	prog_data = (t_program *)data;
	while (!prog_data->stop_flag)
	{
		i = -1;
		while (++i < prog_data->philo_num)
		{
			if (is_dead(prog_data->philos, i))
				break ;
			if (!check_times_eaten(prog_data->each_philo_must_eat_num,
					prog_data->philos[i].times_eaten, &prog_data->stop_flag))
				break ;
		}
	}
	return (NULL);
}
