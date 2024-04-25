/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:31 by jlu               #+#    #+#             */
/*   Updated: 2024/04/25 14:43:00 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *err)
{
	printf("%s\n", err);
	exit (EXIT_FAILURE);

}

t_philo *init_data(long int *nb)
{	
	t_philo *philo;
	
	philo = (t_philo *)ft_calloc(1, sizeof(t_philo));
	if (!philo)
		error_msg(ERR_MEM);
	if (nb[0] < 201)
		philo->num_philo = nb[0];
	else
		error_msg("Too many confucius. It's confusing");
	philo->time_die = nb[1];
	philo->time_eat = nb[2];
	philo->time_sleep = nb[3];
	if (nb[4])
		philo->num_eat = nb[4];
	return (philo);
}

long int	*check_arg(int argc, char *argv[])
{
	int			i;
	long int	*nb;
	
	if (argc < 5 || argc > 6)
		error_msg(ERR_INPUT);
	nb = (long int*)malloc(sizeof(int) * argc - 1);
	if (!nb)
		error_msg(ERR_MEM);
	i = -1;
	while (argv[++i + 1])
		nb[i] = ft_atol(argv[i + 1]);
	nb[i] = '\0';
	i = -1;
	while (++i < 5)
	{
		if (nb[i] <= 0 && i != 4)
			error_msg(ERR_AG);
		if (i == 4 && nb[i] < 0)
			error_msg(ERR_AG);
	}
	return (nb);
}

int	main(int argc, char *argv[])
{
	t_philo *philo;
	long int *input;
	
	input = check_arg(argc, argv);
	philo = init_data(input);
	printf("Num of philos: %ld\n", philo->num_philo);
	printf("Death timer: %ld\n", philo->time_die);
	printf("break timer: %ld\n", philo->time_eat);
	printf("sleep timer: %ld\n", philo->time_sleep);
	if (philo->num_eat)
		printf("Number of time to eat: %ld\n", philo->num_eat);

	return 0;
}

