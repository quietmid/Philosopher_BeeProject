/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:34:19 by jlu               #+#    #+#             */
/*   Updated: 2024/04/26 12:09:16 by jlu              ###   ########.fr       */
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
# include <sys/time.h>

// err
# define ERR_INPUT "Confucius says, try again"
# define ERR_AG "Invalid Arguments"
# define ERR_MEM "Memry allocation fails"

struct s_philo;

typedef struct s_confucius
{
	int				id;
	int				meal_ate;
	int				l_fork;
	int				r_fork;
	long long		t_last_meal;
	pthread_t		thread;
	struct s_philo 	*philo;
}		t_confucius;

typedef struct s_philo
{
	long int		num_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				num_eat;
	int				dead_flag;
	long int		start_time;
	pthread_mutex_t	fork[201];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	t_confucius		thinkers[201];
}		t_philo;

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

long int	error_msg(char *err);

//parsing
int		ft_atol(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	init_data(char *argv[], t_philo *philo);
void	init_thinker(t_philo *philo);
int		init_mutex(t_philo *philo);

#endif