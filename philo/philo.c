/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:31 by jlu               #+#    #+#             */
/*   Updated: 2024/04/23 16:10:56 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void	error_msg(char *err)
//{
//	printf("%s\n", err);
//	exit (EXIT_FAILURE);

//}

//int	check_arg(int argc, char *argv[])
//{
//	int	i;
	
//	if (argc < 5)
//		error_msg(ERR_INPUT);
//	i = 2;
//	// atol each argv to int
//}

int	main(int argc, char *argv[])
{
	int i;
	long int nb;

	i = 1;
	while (argv[i])
	{	
		nb = ft_atol(argv[i]);
		printf("%ld\n", nb);
		i++;
	}
	
	return 0;
}

