/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:45:24 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/25 16:44:21 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(useconds_t usec)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;
	long long		rem;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (true)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000LL
			+ (current.tv_usec - start.tv_usec);
		if (elapsed >= usec)
			break ;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}
