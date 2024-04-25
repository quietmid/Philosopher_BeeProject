/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:34:19 by jlu               #+#    #+#             */
/*   Updated: 2024/04/25 14:16:14 by jlu              ###   ########.fr       */
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
# define ERR_INPUT "Confucius says, try again"
# define ERR_AG "Invalid Arguments"
# define ERR_MEM "Memry allocation fails"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	long int		num_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		num_eat;
	long int		start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}		t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
}		t_program;
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

void	error_msg(char *err);

//parsing
int	ft_atol(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif