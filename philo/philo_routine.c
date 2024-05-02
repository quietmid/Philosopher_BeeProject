/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/05/03 01:39:54 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_checker(t_data *r, t_philo *p)
{
	int i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->num_philo && !(r->dead_flag))
		{
			pthread_mutex_lock(&(r->meal_lock));
			if (time_diff(p[i].t_last_meal, current_timestamp()) > r->time_die)
			{
				action_print(r, i, DEATH);
				r->dead_flag = true;
			}
			pthread_mutex_unlock(&(r->meal_lock));
			usleep(150);
		}
		if (r->dead_flag)
			break ;
		i = 0;
		while (r->num_eat_flag && i < r->num_philo && p[i].meal_ate >= r->num_eat)
			i++;
		if (i == r->num_philo)
			r->all_ate = true;
	}
}

void	p_eat(t_philo *philo)
{
	t_data *rules;

	rules = philo->data;
	if (pthread_mutex_lock(&(rules->fork[philo->l_fork])))
		error_msg(ERR_MX);
	action_print(rules, philo->id, FORK);
	if (pthread_mutex_lock(&(rules->fork[philo->r_fork])))
		error_msg(ERR_MX);
	action_print(rules, philo->id, FORK);
	if (pthread_mutex_lock(&(rules->meal_lock)))
		error_msg(ERR_MX);
	action_print(rules, philo->id, EAT);
	philo->t_last_meal = current_timestamp();
	if (pthread_mutex_unlock(&(rules->meal_lock)))
		error_msg(ERR_MX);
	philo->meal_ate += 1;
	usleep(rules->time_eat);
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
	if (philo->id % 2)
		usleep(15000); // should the smart sleep timer be flexible. based on the eating time and sleep timer?
	// add a rule to separate the philosopher. some sleep first 
	// to make sure there is no deadlock
	while (rules->dead_flag != 1)
	{
		p_eat(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, SLEEP); // they sleep first
		usleep(rules->time_sleep);
		action_print(rules, philo->id, THINK);//they think
	}
	return(NULL);
}
void	end_rountine(t_data *r, t_philo *p)
{
	int i;

	i = -1;
	while (++i < r->num_philo)
		pthread_join(p[i].thread, NULL);
	i = -1;
	while (++i < r->num_philo)
		pthread_mutex_destroy(&(r->fork[i]));
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
	death_checker(rules, philo); // monitor death and num_eat
	end_rountine(rules, philo);
	return (0);
}