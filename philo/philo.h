/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:25:34 by jlu               #+#    #+#             */
/*   Updated: 2024/04/23 16:09:45 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// library headers
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

// err
# define ERR_INPUT "philo trainee, please think again"

//typedef enum State
//{
//	THINKING = 0,
//	HUNGRY = 1,
//	EATING = 2,
//	FULL = 3,
//	SLEEPING = 4,
//	TIRED = 5,
//};

// Functions

//parsing
int	ft_atol(const char *s);

#endif