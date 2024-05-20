/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/05/20 16:05:02 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_time_checker(t_data *r, t_philo *p)
{
	pthread_mutex_lock(&(r->meal_lock));
	if (time_diff(p->t_last_meal, current_timestamp()) > r->time_die)
	{
		p->dead = true;
		pthread_mutex_unlock(&(r->meal_lock));
		action_print(r, p->id, DEATH);
		return (1);
	}
	pthread_mutex_unlock(&(r->meal_lock));
	return (0);
}

void	death_checker(t_data *r, t_philo *p, int i)
{
	if (i == r->num_philo)
	{
		while (1)
		{
			if (allp_ate(r, p))
				break ;
			if (philo_dead(r, p))
				break ;
		}
	}
	else
	{
		pthread_mutex_lock(&(r->dead_lock));
		r->exit = true;
		pthread_mutex_unlock(&(r->dead_lock));
	}
}

int	p_eat(t_philo *p)
{
	t_data	*r;

	r = p->data;
	pthread_mutex_lock(&(r->fork[p->l_fork]));
	p->fork_l = true;
	action_print(r, p->id, FORK);
	if (r->num_philo == 1)
	{
		all_putdown(r, p);
		return (1);
	}
	pthread_mutex_lock(&(r->fork[p->r_fork]));
	p->fork_r = true;
	action_print(r, p->id, FORK);
	eating(r, p);
	all_putdown(r, p);
	return (0);
}

void	*p_day(void *void_philo)
{
	t_philo		*p;
	t_data		*r;

	p = (t_philo *)void_philo;
	r = p->data;
	if (!(p->id % 2))
	{
		action_print(r, p->id, THINK);
		sleeper(r, ((r->time_eat) / 2));
	}
	while (!p_is_dead(p, r) && !is_exit(r))
	{
		if (p_eat(p))
			break ;
		if (sleeping(r, p))
			break ;
		if (thinking(r, p))
			break ;
	}
	if (is_exit(r))
		all_putdown(r, p);
	return (NULL);
}

int	philo_rountine(t_data *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start_time = current_timestamp();
	i = 0;
	while (i < rules->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &p_day, &(philo[i])))
		{
			error_msg("Thread creations failed");
			break ;
		}
		pthread_mutex_lock(&(rules->meal_lock));
		philo[i].t_last_meal = current_timestamp();
		pthread_mutex_unlock(&(rules->meal_lock));
		i++;
	}
	death_checker(rules, rules->philo, i);
	while (--i >= 0)
		if (pthread_join(philo[i].thread, NULL))
			error_msg_free("thread joining failed", rules);
	end_rountine(rules);
	return (0);
}
