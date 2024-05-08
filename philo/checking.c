/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:41:55 by jlu               #+#    #+#             */
/*   Updated: 2024/05/08 22:10:16 by jlu              ###   ########.fr       */
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

	pthread_mutex_lock(&(r->alleat_lock));
	i = r->all_ate;
	pthread_mutex_unlock(&(r->alleat_lock));
	return (i);
}

bool p_is_full(t_philo *p, t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->alleat_lock));
	//pthread_mutex_lock(&(p->p_meallock));
	i = p->full;
	//pthread_mutex_unlock(&(p->p_meallock));
	pthread_mutex_unlock(&(r->alleat_lock));
	return (i);
}

bool p_is_dead(t_philo *p, t_data *r)
{
	bool i;

	pthread_mutex_lock(&(r->p_lock));
	//pthread_mutex_lock(&(p->p_deadlock));
	i = p->dead;
	//pthread_mutex_unlock(&(p->p_deadlock));
	pthread_mutex_unlock(&(r->p_lock));
	return (i);
}
