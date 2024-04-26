/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:40:34 by jlu               #+#    #+#             */
/*   Updated: 2024/04/26 13:44:43 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	init_thinker(t_philo *philo)
{
	int	i;

	i = philo->num_philo;
	//printf("The number of Confusius is: %d\n", i);
	while (--i >= 0)
	{
		philo->thinkers[i].id = i;
		//printf("Confusius[%d]\n", i);
		philo->thinkers[i].meal_ate = 0;
		philo->thinkers[i].l_fork = i;
		//printf("has l_fork id: %d", i);
		if (i == 0)
		{
			philo->thinkers[i].r_fork = philo->num_philo - 1;
			//printf(" and r_fork id: %d", philo->thinkers[i].r_fork);
		}
		else
		{
			philo->thinkers[i].r_fork = i - 1;
			//printf(" and r_fork id: %d\n", philo->thinkers[i].r_fork);
		}
		philo->thinkers[i].t_last_meal = 0;
		philo->thinkers[i].philo = philo;
	}
}

int	init_mutex(t_philo *philo)
{
	int i;

	i = philo->num_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(philo->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(philo->write_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(philo->meal_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(philo->dead_lock), NULL))
		return (1);
	return (0);
}

int	init_data(char *argv[], t_philo *philo)
{
	philo->num_philo = ft_atol(argv[1]);
	philo->time_die = ft_atol(argv[2]);
	philo->time_eat = ft_atol(argv[3]);
	philo->time_sleep = ft_atol(argv[4]);
	philo->dead_flag = 0;
	philo->start_time = 0;
	if (philo->num_philo < 1 || philo->time_die < 1 \
	|| philo->time_eat < 1 || philo->time_sleep < 1)
		error_msg(ERR_AG);
	if (philo->num_philo > 200)
		error_msg("Too many confucius. It's confusing");
	if (argv[5] != '\0')
	{
		philo->num_eat = ft_atol(argv[5]);
		if (philo->num_eat <= 0)
			error_msg(ERR_AG);
	}
	if (argv[5] == '\0')
		philo->num_eat = '\0';
	if (init_mutex(philo) == 1)
		error_msg("You can't lock this!");
	init_thinker(philo);
	return (0);
}