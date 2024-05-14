/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:09:00 by jlu               #+#    #+#             */
/*   Updated: 2024/05/14 16:55:17 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	error_msg(char *err)
{
	printf("%s\n", err);
	return (1);
}

void	action_print(t_data *rules, int id, char *message)
{
	pthread_mutex_lock(&(rules->write_lock));
	// if (!is_exit(rules))
	{
		printf("%ld ", current_timestamp() - rules->start_time);
		printf("%d %s\n", id + 1, message);
	}
	pthread_mutex_unlock(&(rules->write_lock));
}

// int main()
// {
// 	t_philo *philo = malloc(sizeof(t_philo));
// 	if (!philo)
// 		return 1;
// 	int id = 0;

// 	philo->dead_flag = 0;
// 	philo->start_time = current_timestamp();
// 	action_print(philo, id, FORK);
// 	sleep(3);
// 	action_print(philo, id + 1, FORK);
// 	sleep(5);
// 	action_print(philo, id + 2, FORK);
// 	free(philo);
// 	return (0);
// }