/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/26 21:46:46 by jlu              ###   ########.fr       */
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
void	*p_day(void *void_philo)
{
	int			i;
	t_philo		*philo;

	i = 0;
	philo = (t_philo *)void_philo;
	while (!(philo->dead_flag))
	{
		if (pthread_mutex_lock(&(philo->fork[philo->thinkers->l_fork])) != 0)
			error_msg("Lock aint working");
		action_print()
	}
}

int	philo_rountine(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_create(&(philo->thinkers[i].thread), NULL, &p_day, &philo->thinkers[i]) != 0)
			error_msg("No thread today");
		i++;
	}
}