/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/04/30 19:55:00 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *philo)
{
	t_data *rules;

	rules = philo->data;
	if (pthread_mutex_lock(&(rules->fork[philo->l_fork])))
		error_msg(ERR_MX);
	action_print(philo, philo->id, FORK);
	if (pthread_mutex_lock(&(rules->fork[philo->r_fork])))
		error_msg(ERR_MX);
	action_print(philo, philo->id, FORK);
	if (pthread_mutex_lock(&(rules->meal_lock)))
		error_msg(ERR_MX);
	action_print(philo, philo->id, EAT);
	philo->t_last_meal = current_timestamp();
	if (pthread_mutex_unlock(&(rules->meal_lock)))
		error_msg(ERR_MX);
	philo->meal_ate += 1;
	// make sure they eat for the amount of time that's given
	if (pthread_mutex_unlock(&(rules->fork[philo->l_fork])))
		error_msg(ERR_MX);
	if (pthread_mutex_unlock(&(rules->fork[philo->r_fork])))
		error_msg(ERR_MX);
}
void	*p_day(void *void_philo)
{
	t_philo		*philo;
	t_data		*rules;

	philo = (t_philo *)void_philo;
	rules = philo->data;
	// add a rule to separate the philosopher. some sleep first 
	// to make sure there is no deadlock
	while (rules->dead_flag != 1)
	{
		p_eat(philo);
		if (rules->all_ate)
			break ;
		action_print(philo, philo->id, SLEEP); // they sleep first
		//actually need a sleep function for the amount of time that they need 
		action_print(philo, philo->id, THINK);//they think
	}
}

int	philo_rountine(t_data *rules)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = rules->philo;
	rules->start_time = current_timestamp();
	while (i < rules->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &p_day, &(philo[i])))
			error_msg("No thread today");
		// if meal_ate then
		philo[i].t_last_meal = current_timestamp();
		i++;
	}
	// monitor functions
	return (0);
}