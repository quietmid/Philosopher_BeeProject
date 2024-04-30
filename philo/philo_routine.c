/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/30 13:21:52 by jlu              ###   ########.fr       */
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
	t_philo		*kong;
	t_data		*data;


	i = 0;
	kong = (t_philo *)void_philo;
	data = kong->data;
	while (data->dead_flag != 1)
	{
		if (pthread_mutex_lock(&(data->fork[kong->l_fork])))
			error_msg("Lock aint working");
		action_print(&data, kong->id, FORK);
	}
}

int	philo_rountine(t_data *rules)
{
	int i;
	t_philo *kong;

	i = 0;
	kong = rules->philo;
	rules->start_time = current_timestamp();
	while (i < rules->num_philo)
	{
		if (pthread_create(&(kong[i].thread), NULL, &p_day, &(kong[i])))
			error_msg("No thread today");
		// if meal_ate then
		kong[i].t_last_meal = current_timestamp();
		i++;
	}
}