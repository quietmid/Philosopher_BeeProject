/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:02:30 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 18:41:23 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_data *r, t_philo *p)
{
	action_print(r, p->id, EAT);
	pthread_mutex_lock(&(r->meal_lock));
	p->t_last_meal = current_timestamp();
	(p->meal_ate)++;
	if (r->num_eat_flag && p->meal_ate == r->num_eat)
	{
		p->full = true;
		pthread_mutex_unlock(&(r->meal_lock));
		sleeper(r, r->time_eat);
		return (1);
	}
	pthread_mutex_unlock(&(r->meal_lock));
	sleeper(r, r->time_eat);
	return (0);
}

void	all_putdown(t_data *r, t_philo *p)
{
	if (p->fork_l == true)
	{
		pthread_mutex_unlock(&(r->fork[p->l_fork]));
		p->fork_l = false;
	}
	if (p->fork_r == true)
	{
		pthread_mutex_unlock(&(r->fork[p->r_fork]));
		p->fork_r = false;
	}
}

int	sleeping(t_data *r, t_philo *p)
{
	if (is_exit(r))
		return (1);
	action_print(r, p->id, SLEEP);
	sleeper(r, r->time_sleep);
	return (0);
}

int	thinking(t_data *r, t_philo *p)
{
	if (is_exit(r))
		return (1);
	action_print(r, p->id, THINK);
	return (0);
}
