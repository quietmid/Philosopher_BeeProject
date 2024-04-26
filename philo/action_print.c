/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:09:00 by jlu               #+#    #+#             */
/*   Updated: 2024/04/26 14:15:42 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	error_msg(char *err)
{
	printf("%s\n", err);
	return (1);
}

void	action_print(int timestamp, int id, char *message)
{
	printf("%d %d %s", timestamp, id, message);
}
