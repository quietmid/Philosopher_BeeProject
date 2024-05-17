/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_seconds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:49:59 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 19:18:33 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	current_timestamp(void)
{
	struct timeval	time;
	long int		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

long	time_diff(long int l_eat, long int now)
{
	long int	time_diff;

	time_diff = now - l_eat;
	return (time_diff);
}

void	sleeper(t_data *r, long int time)
{
	long int	i;

	i = current_timestamp();
	while (!is_exit(r))
	{
		if (time_diff(i, current_timestamp()) >= time)
			break ;
		usleep(100);
	}
}
