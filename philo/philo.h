/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:25:34 by jlu               #+#    #+#             */
/*   Updated: 2024/04/22 17:40:02 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// library headers
# include<string.h>
# include<pthread.h>
# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>

typedef enum State
{
	THINKING = 0,
	HUNGRY = 1,
	EATING = 2,
	FULL = 3,
	SLEEPING = 4,
	TIRED = 5,
};

#endif