/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/18 16:23:54 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/time.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_program
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				each_philo_must_eat_num;
}	t_program;

typedef struct s_philo
{
	t_program		*prog_data;
	pthread_t		th;
	pthread_mutex_t	*fork;
	int				id;
	int				times_eaten;
}	t_philo;

int		ft_atoi(const char *str);
void	launch_philos(t_program *data, int	*error_flag);
void	*routine(void *data);

#endif