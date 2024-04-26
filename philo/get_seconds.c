/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_seconds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:49:59 by jlu               #+#    #+#             */
/*   Updated: 2024/04/26 21:55:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_timestamp(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000LL + time.tv_usec / 1000;
	return (ms);
}
