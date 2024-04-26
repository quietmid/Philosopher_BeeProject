/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/26 14:28:09 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//philo rountine () executed over and over by the philos until the dead_flag = 1
/*
while ()
{
	if (philo[1].thinkig != 1 && left fork == available)
		pick up the left fork
		if (right fork == available)
			pick up
		else
			drop the left work
		if (both fork available)
			eat	
}

check 
	if (dead_flag == 1 || meals_eaten == num_eat)
		exit
*/
void	*p_day()
{
	
}

int	philo_rountine(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_create(&(philo->thinkers[i].thread), NULL, &p_day, /*the argument for p_day)*/ != 0))
			error_msg("No thread today");
		i++;
	}
}