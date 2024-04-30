/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:34:19 by jlu               #+#    #+#             */
/*   Updated: 2024/04/30 20:17:50 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// library headers
# include <string.h>
# include <stdbool.h> // to check if the thinker is full or not
# include <pthread.h> // pthread, mutex
# include <unistd.h> // usleep
# include <stdlib.h> // malloc
# include <stdio.h> // printf
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX | LONG_MAX

// err
# define ERR_INPUT "Confucius says, try again"
# define ERR_AG "Invalid Arguments"
# define ERR_MEM "Memry allocation fails"
# define ERR_MX "Mutex Fails"

// Philo Actions
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"

struct s_philo;

typedef struct s_philo
{
	int				id;
	int				meal_ate;
	int				l_fork;
	int				r_fork;
	bool			full;
	long long		t_last_meal;
	pthread_t		thread;
	struct s_data 	*data;
}		t_philo;

typedef struct s_data
{
	long int		num_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				num_eat;
	bool			dead_flag;
	bool			all_ate;
	bool			num_eat_flag;
	long long		start_time;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	t_philo		philo[200];
}		t_data;

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
void		action_print(t_data *rules, int id, char *message);

//parsing
int		ft_atol(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

// initizalizer

int		init_data(char *argv[], t_data *rules);
void	init_thinker(t_data *rules);
int		init_mutex(t_data *rules);

// utils
long long current_timestamp(void);

//threading
int		philo_rountine(t_data *rules);
void	*p_day(void *void_philo);
void	p_eat(t_philo *philo);

#endif