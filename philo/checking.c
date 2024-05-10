/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:41:55 by jlu               #+#    #+#             */
/*   Updated: 2024/05/10 18:13:47 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool is_exit(t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->dead_lock));
	i = r->exit;
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

