/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:08:32 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/01 22:26:29 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine_one_philo(void *data)
{
	t_program		*prog_d;
	pthread_mutex_t	fork;

	prog_d = (t_program *)data;
	pthread_mutex_init(&fork, NULL);
	pthread_mutex_lock(&fork);
	printf("0 1 has taken a fork\n");
	ft_usleep(prog_d->time_to_die_us);
	printf("%ld 1 died\n", prog_d->time_to_die_us / 1000);
	pthread_mutex_unlock(&fork);
	pthread_mutex_destroy(&fork);
	return (NULL);
}

void	handle_one_philo(t_program *data)
{
	pthread_t	th;

	if (pthread_create(&th, NULL, routine_one_philo, data) != 0)
		return ;
	if (pthread_join(th, NULL) != 0)
		return ;
}
