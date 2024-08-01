/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/01 22:25:41 by sganiev          ###   ########.fr       */
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
	pthread_t			th_monitoring;
	pthread_mutex_t		stop_flag_mutex_prog;
	pthread_mutex_t		is_ready_mutex;
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
	pthread_mutex_t		last_meal_time_mutex;
	pthread_mutex_t		is_full_mutex;
	int					id;
	long				times_eaten;
	long				time_to_sleep_us;
	long				time_to_eat_us;
	long				philo_num;
	long				must_eat_num;
	unsigned long long	last_meal_time;
	unsigned long long	start_time;
	bool				is_full;
	bool				stop_flag;
	bool				is_visited;
};

long				ft_atol(const char *str);
void				ft_usleep(useconds_t usec);
void				print_message(t_philo *philo, char *message);
unsigned long long	take_time(t_time_units type);

int					launch_philos(t_program *data);
void				mutexes_init(t_program *data);
void				free_alloc_data(t_program *data, int *err_flag);
void				*routine(void *data);
void				*monitoring(void *data);
void				create_monitor(t_program *data);
void				stop_all_philos(t_philo *philos, long philo_num);

bool				get_bool_var(pthread_mutex_t *mutex, bool *value);
void				set_bool_var(pthread_mutex_t *mutex, bool value, bool *dst);
unsigned long long	get_ullong_var(pthread_mutex_t *mutex,
						unsigned long long *value);
void				set_ullong_var(pthread_mutex_t *mutex,
						unsigned long long value, unsigned long long *dst);
long				get_long_var(pthread_mutex_t *mutex, long *value);
void				set_long_var(pthread_mutex_t *mutex, long value, long *dst);

void				increment_long(pthread_mutex_t *mutex, long *var);

int					ft_isdigit(int c);
int					ft_isspace(char c);

void				handle_one_philo(t_program *data);
void				*routine_one_philo(void *data);

#endif