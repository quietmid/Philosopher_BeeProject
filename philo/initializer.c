/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:40:34 by jlu               #+#    #+#             */
/*   Updated: 2024/04/30 20:09:12 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	init_thinker(t_data *rules)
{
	int	i;

	i = rules->num_philo;
	//printf("The number of Confusius is: %d\n", i);
	while (--i >= 0)
	{
		rules->philo[i].id = i;
		//printf("Confusius[%d]\n", i);
		rules->philo[i].meal_ate = 0;
		rules->philo[i].l_fork = i;
		//printf("has l_fork id: %d", i);
		if (i == 0)
		{
			rules->philo[i].r_fork = rules->num_philo - 1;
			//printf(" and r_fork id: %d", philo->thinkers[i].r_fork);
		}
		else
		{
			rules->philo[i].r_fork = i - 1;
			//printf(" and r_fork id: %d\n", philo->thinkers[i].r_fork);
		}
		rules->philo[i].t_last_meal = 0;
		rules->philo[i].data = rules;
		rules->philo[i].full = false;
	}
}

int	init_mutex(t_data *rules)
{
	int i;

	i = rules->num_philo;
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
	rules->dead_flag = 0;
	rules->start_time = 0;
	rules->all_ate = false;
	if (rules->num_philo < 1 || rules->time_die < 1 \
	|| rules->time_eat < 1 || rules->time_sleep < 1)
		error_msg(ERR_AG);
	if (rules->num_philo > 200)
		error_msg("Too many confucius. It's confusing");
	if (argv[5])
	{
		rules->num_eat = ft_atol(argv[5]);
		if (rules->num_eat <= 0)
			error_msg(ERR_AG);
		rules->num_eat_flag = true;
	}
	if (init_mutex(rules) == 1)
		error_msg("You can't lock this!");
	init_thinker(rules);
	return (0);
}
