/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:04:15 by sganiev           #+#    #+#             */
/*   Updated: 2024/06/15 16:37:45 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positiv(char **nums)
{
	int	i;

	i = 1;
	while (i < 6)
	{
		if (ft_atoi(nums[i++]) <= 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (argc == 6 && is_positiv(argv))
	{
	}
	return (0);
}
