/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:31 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 23:39:40 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_rountine(t_data *r)
{
	int		i;
	t_philo	*p;

	p = r->philo;
	i = -1;
	while (++i < r->num_philo)
	{
		if (&(r->fork[i]) != NULL)
			pthread_mutex_destroy(&(r->fork[i]));
	}
	if (&(r->write_lock) != NULL)
		pthread_mutex_destroy(&(r->write_lock));
	if (&(r->dead_lock) != NULL)
		pthread_mutex_destroy(&(r->dead_lock));
	if (&(r->meal_lock) != NULL)
		pthread_mutex_destroy(&(r->meal_lock));
	if (r->fork)
		free(r->fork);
	if (p)
		free (p);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	check_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		rules;
	int			i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (error_msg(ERR_INPUT));
	while (i < argc)
	{
		if (check_arg(argv[i]))
			return (error_msg(ERR_INPUT));
		i++;
	}
	if (init_data(argv, &rules))
		return (error_msg("Init failed"));
	if (philo_rountine(&rules))
		return (error_msg("philo routine failed"));
	return (0);
}
