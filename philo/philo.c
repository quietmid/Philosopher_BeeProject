/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:31 by jlu               #+#    #+#             */
/*   Updated: 2024/05/15 19:05:57 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_rountine(t_data *r)
{
	int i;

	i = -1;
	while (++i < r->num_philo)
		pthread_mutex_destroy(&(r->fork[i]));
	pthread_mutex_destroy(&(r->write_lock));
	pthread_mutex_destroy(&(r->dead_lock));
	pthread_mutex_destroy(&(r->meal_lock));
}

int	main(int argc, char *argv[])
{
	t_data		rules;
	
	if (argc < 5 || argc > 6)
		return (error_msg(ERR_INPUT, &rules));
	if (init_data(argv, &rules) == 1)
		error_msg("Init failed", &rules);
	if (philo_rountine(&rules))
		error_msg("something something", &rules);
	return 0;
}

	// printf("number of philos: %ld\n", rules.num_philo);
	// printf("number of time to die: %ld\n", rules.time_die);
	// printf("number of time to eat: %ld\n", rules.time_eat);
	// printf("number of time to sleep: %ld\n", rules.time_sleep);
	// if (rules.num_eat_flag)
	// 	printf("number of meals need to be eaten: %d\n", rules.num_eat);