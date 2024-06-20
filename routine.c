/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:48:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/20 15:46:00 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// should you check what is bigger in 'tv_usec'?
// because I think here:
// 'current_time.tv_usec - philo->last_meal_time.tv_usec'
// philo->last_meal_time.tv_usec couls be bigger

// There’s no mechanism to print a message or handle the 
// case when a philosopher dies

static int	check_last_meal_time(t_philo *philo)
{
	struct timeval		current_time;
	unsigned long long	elapsed;

	gettimeofday(&current_time, NULL);
	elapsed = (current_time.tv_sec * 1000000 + current_time.tv_usec)
		- (philo->last_meal_time.tv_sec * 1000000
			+ philo->last_meal_time.tv_usec);
	if (elapsed >= philo->prog_data->time_to_die)
		return (0);
	else
		return (1);
}

static int	check_times_eaten(t_philo *philo)
{
	if (philo->prog_data->each_philo_must_eat_num == -1)
		return (1);
	if (philo->times_eaten < philo->prog_data->each_philo_must_eat_num)
		return (1);
	else
		return (0);
}

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	gettimeofday(&philo->last_meal_time, NULL);
	while (check_last_meal_time(philo) && check_times_eaten(philo))
	{
		take_forks_and_eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
