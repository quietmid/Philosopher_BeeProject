/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:31 by jlu               #+#    #+#             */
/*   Updated: 2024/04/30 20:23:48 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		rules;
	
	if (argc < 5 || argc > 6)
		return (error_msg(ERR_INPUT));
	if (init_data(argv, &rules) == 1)
		error_msg("Init failed");
	if (philo_rountine(&rules))
		error_msg("something something");
	// printf("number of philos: %ld\n", rules.num_philo);
	// printf("number of time to die: %ld\n", rules.time_die);
	// printf("number of time to eat: %ld\n", rules.time_eat);
	// printf("number of time to sleep: %ld\n", rules.time_sleep);
	// if (rules.num_eat_flag)
	// 	printf("number of meals need to be eaten: %d\n", rules.num_eat);
	//free struct philo and input
	return 0;
}

	// printf("number of philos: %ld\n", rules.num_philo);
	// printf("number of time to die: %ld\n", rules.time_die);
	// printf("number of time to eat: %ld\n", rules.time_eat);
	// printf("number of time to sleep: %ld\n", rules.time_sleep);
	// if (rules.num_eat_flag)
	// 	printf("number of meals need to be eaten: %d\n", rules.num_eat);