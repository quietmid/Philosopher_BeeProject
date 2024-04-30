/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:31 by jlu               #+#    #+#             */
/*   Updated: 2024/04/30 19:12:44 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	error_msg(char *err)
{
	printf("%s\n", err);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data		rules;
	
	if (argc < 5 || argc > 6)
		return (error_msg(ERR_INPUT));
	if (init_data(argv, &rules) == 1)
		error_msg("Init failed");
	//free struct philo and input
	return 0;
}

	//printf("number of philos: %ld\n", philo.num_philo);
	//printf("number of time to die: %ld\n", philo.time_die);
	//printf("number of time to eat: %ld\n", philo.time_eat);
	//printf("number of time to sleep: %ld\n", philo.time_sleep);
	//printf("number of meals need to be eaten: %d\n", philo.num_eat);