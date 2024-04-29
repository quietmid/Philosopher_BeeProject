/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/29 15:38:27 by jlu              ###   ########.fr       */
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
	t_confucius	*kong;
	t_philo		*philo;


	i = 0;
	kong = (t_confucius *)void_philo;
	philo = kong->philo;
	while (philo->dead_flag != 1)
	{
		if (pthread_mutex_lock(&(philo->fork[kong->l_fork])) != 0)
			error_msg("Lock aint working");
		action_print();
	}
}

int	philo_rountine(t_philo *philo)
{
	int i;
	t_confucius *kong;

	i = 0;
	kong = philo->thinkers;
	philo->start_time = current_timestamp();
	while (i < philo->num_philo)
	{
		if (pthread_create(&(kong[i].thread), NULL, &p_day, &(kong[i])) != 0)
			error_msg("No thread today");
		kong[i].t_last_meal = current_timestamp();
		i++;
	}
}