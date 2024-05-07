/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/05/07 18:24:20 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_time_checker(t_data *r, t_philo *p)
{
	if (time_diff(p->t_last_meal, current_timestamp()) > r->time_die)
	{
		action_print(r, p->id, DEATH);
		p->dead = true;
		return (1);
	}
	return (0);
}

void	death_checker(t_data *r, t_philo *p)
{
	int i;

	while (r->all_ate == false)
	{
		i = -1;
		while (++i < r->num_philo && !(r->dead_flag))
		{
			pthread_mutex_lock(&(r->meal_lock));
			pthread_mutex_lock(&(r->dead_lock));
			r->dead_flag = meal_time_checker(r, p);
			pthread_mutex_unlock(&(r->dead_lock));
			pthread_mutex_unlock(&(r->meal_lock));
			usleep(150);
		}
		if (r->dead_flag)
			break ;
		i = 0;
		while (r->num_eat_flag && i < r->num_philo && p[i].full == true)
			i++;
		pthread_mutex_lock(&(r->alleat_lock));
		if (i == r->num_philo)
			r->all_ate = true;
		pthread_mutex_unlock(&(r->alleat_lock));
	}
}

void	p_eat(t_philo *philo)
{
	t_data *rules;

	rules = philo->data;
	pthread_mutex_lock(&(rules->fork[philo->l_fork]));
	philo->fork_l = true;
	action_print(rules, philo->id, FORK);
	if (rules->num_philo == 1)
	{
		sleeper(rules, rules->time_die);
		pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
		return ;
	}
	pthread_mutex_lock(&(rules->fork[philo->r_fork]));
	philo->fork_r = true;
	action_print(rules, philo->id, FORK);
	eating(rules, philo);
	sleeper(rules, rules->time_eat);
	put_downforks(&(rules->fork[philo->l_fork]), &(rules->fork[philo->r_fork]));
	if (rules->dead_flag || rules->all_ate)
		all_putdown(rules, philo);
}

void	*p_day(void *void_philo)
{
	t_philo		*philo;
	t_data		*rules;

	philo = (t_philo *)void_philo;
	rules = philo->data;
	if (philo->id % 2)
		usleep((rules->time_sleep)/2);
	while (philo->dead == false && philo->full == false)
	{
		if (rules->all_ate == false)
		{
			p_eat(philo);
			action_print(rules, philo->id, SLEEP); // they sleep first
			sleeper(rules, rules->time_sleep);
			action_print(rules, philo->id, THINK); //they think
		}
		else
			break ;
	}
	return(NULL);
}
//void	end_rountine(t_data *r, t_philo *p)
//{
//	int i;

//	i = -1;
//	while (++i < r->num_philo)
//	{
//		if(pthread_join(p[i].thread, NULL))
//			error_msg("thread failed");
//	}
//	i = -1;
//	while (++i < r->num_philo)
//		pthread_mutex_destroy(&(r->fork[i]));
//	pthread_mutex_destroy(&(r->write_lock));
//	pthread_mutex_destroy(&(r->dead_lock));
//	pthread_mutex_destroy(&(r->alleat_lock));
//}

int	philo_rountine(t_data *rules)
{
	int 		i;
	t_philo 	*philo;

	i = 0;
	philo = rules->philo;
	rules->start_time = current_timestamp();
	while (i < rules->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &p_day, &(philo[i])))
			error_msg("No thread today"); // clear everything
		philo[i].t_last_meal = current_timestamp();
		i++;
	}
	death_checker(rules, rules->philo);
	i = -1;
	while (++i < rules->num_philo)
	{
		if(pthread_join(philo[i].thread, NULL))
			error_msg("thread failed");
	}
	end_rountine(rules);
	return (0);
}
