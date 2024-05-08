/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:02:30 by jlu               #+#    #+#             */
/*   Updated: 2024/05/08 20:58:38 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_downforks(pthread_mutex_t *l_fork, pthread_mutex_t *r_fork, t_philo *p)
{
	if (p->fork_l == true)
	{
		pthread_mutex_unlock(l_fork);
		p->fork_l = false;
	}
	if (p->fork_r == true)
	{
		pthread_mutex_unlock(r_fork);
		p->fork_r = false;
	}
}

void	eating(t_data *r, t_philo *p)
{
	pthread_mutex_lock(&(r->meal_lock));
	action_print(r, p->id, EAT);
	p->t_last_meal = current_timestamp();
	(p->meal_ate)++;
	if (r->num_eat_flag && p->meal_ate == r->num_eat)
			p->full = true;
	pthread_mutex_unlock(&(r->meal_lock));
}

void	all_putdown(t_data *r, t_philo *p)
{
	if (p->fork_l == true)
	{
		pthread_mutex_unlock(&(r->fork[p->l_fork]));
		printf("%d has l fork dropped\n", p->id);
		p->fork_l = false;
	}
	if (p->fork_r == true)
	{
		pthread_mutex_unlock(&(r->fork[p->r_fork]));
		printf("%d has r fork dropped\n", p->id);
		p->fork_r = false;
	}
}