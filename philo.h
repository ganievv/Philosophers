/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:22:33 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/15 16:42:25 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <errno.h>
# include <semaphore.h>
# include <stdbool.h>
# include <time.h>

typedef struct s_philo
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	each_philo_must_eat_num;
}	t_philo;

int	ft_atoi(const char *str);

#endif