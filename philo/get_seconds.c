/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_seconds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:49:59 by jlu               #+#    #+#             */
/*   Updated: 2024/04/29 08:53:53 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_timestamp(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
	return (ms);
}

// int main ()
// {
// 	long long ms_start = current_timestamp();
// 	long long ms_nw;

// 	printf("time of the day: %lld\n", ms_start);
// 	sleep(3);
// 	ms_nw = current_timestamp();
// 	printf("time of the day: %lld\n", ms_nw - ms_start);
// 	sleep(3);
// 	ms_nw = current_timestamp();
// 	printf("time of the day: %lld\n", ms_nw - ms_start);
// 	sleep(5);
// 	ms_nw = current_timestamp();
// 	printf("time of the day: %lld\n", ms_nw - ms_start);
// 	return 0;
// }
