/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:41:55 by jlu               #+#    #+#             */
/*   Updated: 2024/05/10 13:55:09 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool is_dead(t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->dead_lock));
	i = r->dead_flag;
	pthread_mutex_unlock(&(r->dead_lock));
	return (i);
}

bool is_full(t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->dead_lock));
	i = r->all_ate;
	pthread_mutex_unlock(&(r->dead_lock));
	return (i);
}

bool p_is_full(t_philo *p, t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->meal_lock));
	i = p->full;
	pthread_mutex_unlock(&(r->meal_lock));
	return (i);
}

bool p_is_dead(t_philo *p, t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->dead_lock));
	i = p->dead;
	pthread_mutex_unlock(&(r->dead_lock));
	return (i);
}

