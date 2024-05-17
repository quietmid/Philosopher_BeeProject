/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:09:00 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 19:21:03 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *err)
{
	printf("%s\n", err);
	return (1);
}

int	error_msg_free(char *err, t_data *r)
{
	printf("%s\n", err);
	end_rountine(r);
	return (1);
}

void	action_print(t_data *rules, int id, char *message)
{
	pthread_mutex_lock(&(rules->write_lock));
	if (!is_exit(rules))
	{
		printf("%ld ", current_timestamp() - rules->start_time);
		printf("%d %s\n", id + 1, message);
	}
	pthread_mutex_unlock(&(rules->write_lock));
}
