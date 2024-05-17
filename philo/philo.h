/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:34:19 by jlu               #+#    #+#             */
/*   Updated: 2024/05/17 19:16:44 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// library headers
# include <string.h>
# include <stdbool.h> // bool
# include <pthread.h> // pthread, mutex
# include <unistd.h> // usleep
# include <stdlib.h> // malloc
# include <stdio.h> // printf
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX | LONG_MAX

// error
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

//debugging
//#define D_LFORK "dropped LEFT FORK"
//#define D_RFORK "dropped RIGHT FORK"

//struct

struct	s_philo;

typedef struct s_philo
{
	int				id;
	int				meal_ate;
	int				l_fork;
	int				r_fork;
	bool			dead;
	bool			full;
	bool			fork_l;
	bool			fork_r;
	long long		t_last_meal;
	pthread_t		thread;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	long int		num_philo;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	int				num_eat;
	bool			exit;
	bool			num_eat_flag;
	long int		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philo;
}		t_data;

// Functions

// Printing
int			error_msg(char *err);
int			error_msg_free(char *err, t_data *r);
void		action_print(t_data *rules, int id, char *message);

//parsing && initializing
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_atol(const char *s);
int			init_data(char *argv[], t_data *rules);
int			init_thinker(t_data *rules);
int			init_mutex(t_data *rules);

// GetTime
long int	current_timestamp(void);
long int	time_diff(long int l_eat, long int now);
void		sleeper(t_data *r, long int time);

// Checks
int			allp_ate(t_data *r, t_philo *p);
int			philo_dead(t_data *r, t_philo *p);
int			meal_time_checker(t_data *r, t_philo *p);
bool		is_exit(t_data *r);
bool		p_is_full(t_philo *p, t_data *r);
bool		p_is_dead(t_philo *p, t_data *r);
void		death_checker(t_data *r, t_philo *p);

// Philo action
void		all_putdown(t_data *r, t_philo *p);
void		*p_day(void *void_philo);
int			eating(t_data *r, t_philo *p);
int			p_eat(t_philo *philo);
int			sleeping(t_data *r, t_philo *p);
int			thinking(t_data *r, t_philo *p);

// thread create && clean ups
int			philo_rountine(t_data *rules);
void		end_rountine(t_data *r);

#endif