/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:08:32 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/01 22:52:35 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine_one_philo(void *data)
{
	t_program	*prog_d;

	prog_d = (t_program *)data;
	pthread_mutex_lock(&prog_d->forks[0]);
	printf("0 1 has taken a fork\n");
	ft_usleep(prog_d->time_to_die_us);
	printf("%ld 1 died\n", prog_d->time_to_die_us / 1000);
	pthread_mutex_unlock(&prog_d->forks[0]);
	return (NULL);
}

static void	free_alloc(t_program *data)
{
	pthread_mutex_destroy(&data->forks[0]);
	free(data->forks);
}

void	handle_one_philo(t_program *data)
{
	pthread_t	th;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->philo_num);
	if (!data->forks)
		return ;
	pthread_mutex_init(&data->forks[0], NULL);
	if (pthread_create(&th, NULL, routine_one_philo, data) != 0)
		return (free_alloc(data), (void)0);
	if (pthread_join(th, NULL) != 0)
		return (free_alloc(data), (void)0);
	free_alloc(data);
}
