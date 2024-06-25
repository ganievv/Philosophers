/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/25 17:34:06 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Maybe when you check last_meal_time it is not already
// appropriate value and because of that philos are dying 

static int	check_times_eaten(int each_philo_must_eat_num, int times_eaten,
	int *stop_flag)
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
	struct timeval		current_time;
	unsigned long long	elapsed;

	gettimeofday(&current_time, NULL);
	elapsed = (current_time.tv_sec * 1000000 + current_time.tv_usec)
		- (philos[index].last_meal_time.tv_sec * 1000000
			+ philos[index].last_meal_time.tv_usec);
	if (elapsed >= philos->prog_data->time_to_die)
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
