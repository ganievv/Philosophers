/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/19 20:30:24 by sganiev          ###   ########.fr       */
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
	unsigned int	philo_num;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				each_philo_must_eat_num;
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
void	take_forks_and_eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

#endif