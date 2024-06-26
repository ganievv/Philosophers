/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/26 16:33:43 by sganiev          ###   ########.fr       */
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
# include <limits.h>

# define MILLISECONDS 1
# define MICROSECONDS 2

typedef struct s_philo	t_philo;

typedef struct s_program
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_t			th_monitoring;
	unsigned long long	start_time;
	long				philo_num;
	long				time_to_die_us;
	long				time_to_eat_us;
	long				time_to_sleep_us;
	long				each_philo_must_eat_num;
	bool				stop_flag;
	bool				is_ready;
}	t_program;

struct s_philo
{
	t_program			*prog_data;
	pthread_t			th;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					id;
	int					times_eaten;
	unsigned long long	last_meal_time;
};

long				ft_atol(const char *str);
int					launch_philos(t_program *data);
void				*routine(void *data);
void				ft_usleep(useconds_t usec);
void				print_message(t_philo *philo, char *message);
void				*monitoring(void *data);
unsigned long long	take_time(int type);

#endif