/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:40:34 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 23:42:24 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thinker(t_data *r)
{
	int	i;

	i = r->num_philo;
	r->philo = malloc(sizeof(t_philo) * i);
	if (!(r->philo))
		return (error_msg_free("Creation of the minds failed", r));
	while (--i >= 0)
	{
		r->philo[i].id = i;
		r->philo[i].meal_ate = 0;
		r->philo[i].l_fork = i;
		if (i == 0)
			r->philo[i].r_fork = r->num_philo - 1;
		else
			r->philo[i].r_fork = i - 1;
		r->philo[i].t_last_meal = current_timestamp();
		r->philo[i].data = r;
		r->philo[i].full = false;
		r->philo[i].dead = false;
		r->philo[i].fork_l = false;
		r->philo[i].fork_r = false;
	}
	return (0);
}

int	init_mutex(t_data *rules)
{
	int	i;

	i = rules->num_philo;
	rules->fork = malloc(sizeof(pthread_mutex_t) * i);
	if (!(rules->fork))
		return (error_msg_free("fork malloc failed", rules));
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->write_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->dead_lock), NULL))
		return (1);
	return (0);
}

int	init_data(char *argv[], t_data *rules)
{
	rules->num_philo = ft_atol(argv[1]);
	rules->time_die = ft_atol(argv[2]);
	rules->time_eat = ft_atol(argv[3]);
	rules->time_sleep = ft_atol(argv[4]);
	rules->start_time = 0;
	rules->exit = false;
	if (rules->num_philo < 1 || rules->time_die < 1 \
	|| rules->time_eat < 1 || rules->time_sleep < 1)
		return (error_msg(ERR_AG));
	if (rules->num_philo > 199)
		return (error_msg("Too many confucius. It's confusing"));
	if (argv[5])
	{
		rules->num_eat = ft_atol(argv[5]);
		if (rules->num_eat <= 0)
			return (error_msg(ERR_AG));
		rules->num_eat_flag = true;
	}
	else
		rules->num_eat_flag = false;
	if (init_mutex(rules))
		return (error_msg_free("You can't lock this!", rules));
	if (init_thinker(rules))
		return (error_msg_free("brains manufacturing error", rules));
	return (0);
}
