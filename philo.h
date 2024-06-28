/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/28 10:21:13 by sganiev          ###   ########.fr       */
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

typedef enum e_time_units
{
	MILLISECONDS,
	MICROSECONDS,
}	t_time_units;

typedef struct s_philo	t_philo;

typedef struct s_program
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		prog_data_mutex;
	pthread_t			th_monitoring;
	unsigned long long	start_time;
	long				philo_num;
	long				time_to_die_us;
	long				time_to_eat_us;
	long				time_to_sleep_us;
	long				each_philo_must_eat_num;
	bool				stop_flag;
	bool				is_ready;
	bool				monitor_start;
}	t_program;

struct s_philo
{
	t_program			*prog_data;
	pthread_t			th;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_mutex;
	int					id;
	long				times_eaten;
	long				time_to_sleep_us;
	long				time_to_eat_us;
	unsigned long long	last_meal_time;
};

long				ft_atol(const char *str);
int					launch_philos(t_program *data);
void				*routine(void *data);
void				ft_usleep(useconds_t usec, t_program *prog_data);
void				print_message(t_philo *philo, char *message);
void				*monitoring(void *data);
unsigned long long	take_time(t_time_units type);
void				activate_threads_and_monitor(t_program *data,
						int *err_flag);

bool				get_bool_var(pthread_mutex_t *mutex, bool *value);
void				set_bool_var(pthread_mutex_t *mutex, bool value, bool *dst);
unsigned long long	get_ullong_var(pthread_mutex_t *mutex,
						unsigned long long *value);
void				set_ullong_var(pthread_mutex_t *mutex,
						unsigned long long value, unsigned long long *dst);
long				get_long_var(pthread_mutex_t *mutex, long *value);
void				set_long_var(pthread_mutex_t *mutex, long value, long *dst);


#endif