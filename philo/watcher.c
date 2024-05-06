/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:20:38 by jlu               #+#    #+#             */
/*   Updated: 2024/05/06 18:43:53 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_checker(t_data *r, t_philo *p)
{
	int i;

	printf("im here\n");
	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->num_philo && !(r->dead_flag))
		{
			pthread_mutex_lock(&(r->meal_lock));
			if (time_diff(p[i].t_last_meal, current_timestamp()) > r->time_die)
			{
				action_print(r, i, DEATH);
				pthread_mutex_lock(&(r->dead_lock));
				r->dead_flag = true;
			}
			pthread_mutex_unlock(&(r->meal_lock));
			if (!(r->dead_flag))
				usleep(150);
		}
		if (r->dead_flag)
		{
			pthread_mutex_unlock(&(r->dead_lock));
			return (1);
		}
	}
	return (0);
}

int	meal_watcher(t_data *r, t_philo *p)
{
	int	i;

	i = 0;
	printf("im here2\n");
	while (!(r->dead_flag))
	{
		while (r->num_eat_flag && i < r->num_philo && p[i].meal_ate >= r->num_eat)
			i++;
		if (i == r->num_philo)
		{
			r->all_ate = true;
			return (1);
		}
	}
	return (0);
}

void	*watcher(void *void_philo)
{
	t_data	*r;
	t_philo	*p;

	p = (t_philo *)void_philo;
	r = p->data;
	while (1)
	{
		if (death_checker(r, p) == 1 || meal_watcher(r, p) == 1)
			break ;
	}
	return (NULL);
}