/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:41:55 by jlu               #+#    #+#             */
/*   Updated: 2024/05/20 15:06:34 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_exit(t_data *r)
{
	bool	i;

	pthread_mutex_lock(&(r->dead_lock));
	i = r->exit;
	pthread_mutex_unlock(&(r->dead_lock));
	return (i);
}

bool	p_is_full(t_philo *p, t_data *r)
{
	bool	i;

	pthread_mutex_lock(&(r->meal_lock));
	i = p->full;
	pthread_mutex_unlock(&(r->meal_lock));
	return (i);
}

bool	p_is_dead(t_philo *p, t_data *r)
{
	bool	i;

	pthread_mutex_lock(&(r->meal_lock));
	i = p->dead;
	pthread_mutex_unlock(&(r->meal_lock));
	return (i);
}

int	allp_ate(t_data *r, t_philo *p)
{
	int	i;

	if (r->num_eat_flag)
	{
		i = 0;
		while (i < r->num_philo && p_is_full(&p[i], r))
		{
			i++;
			if (i == r->num_philo)
			{
				pthread_mutex_lock(&(r->dead_lock));
				r->exit = 1;
				pthread_mutex_unlock(&(r->dead_lock));
				return (1);
			}
		}
	}
	return (0);
}

int	philo_dead(t_data *r, t_philo *p)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		if (meal_time_checker(r, &p[i]))
		{
			pthread_mutex_lock(&(r->dead_lock));
			r->exit = 1;
			pthread_mutex_unlock(&(r->dead_lock));
			return (1);
		}
		i++;
	}
	return (0);
}
