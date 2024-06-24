/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/24 15:15:37 by sganiev          ###   ########.fr       */
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

typedef struct s_philo	t_philo;

typedef struct s_program
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
	pthread_t		th_monitoring;
	unsigned int	philo_num;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				each_philo_must_eat_num;
	int				stop_flag;
	unsigned int	is_ready;
}	t_program;

struct s_philo
{
	t_program		*prog_data;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				times_eaten;
	struct timeval	last_meal_time;
};

int		ft_atoi(const char *str);
int		launch_philos(t_program *data);
void	*routine(void *data);
void	ft_usleep(useconds_t usec);
void	print_message(t_philo *philo, char *message);
void	*verify_death(void *data);

#endif