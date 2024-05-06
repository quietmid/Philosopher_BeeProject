/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/05/06 20:39:49 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_checker(t_data *r, t_philo *p)
{
	int i;

	while (r->all_ate == false)
	{
		i = -1;
		while (++i < r->num_philo && !(r->dead_flag))
		{
			pthread_mutex_lock(&(r->meal_lock));
			if (time_diff(p[i].t_last_meal, current_timestamp()) > r->time_die)
			{
				action_print(r, i, DEATH);
				pthread_mutex_lock(&(r->dead_lock));
				p[i].dead = true;
				r->dead_flag = true;
				pthread_mutex_unlock(&(r->dead_lock));
			}
			pthread_mutex_unlock(&(r->meal_lock));
			usleep(150);
		}
		if (r->dead_flag)
			break ;
		i = 0;
		while (r->num_eat_flag && i < r->num_philo && p[i].full == true)
			i++;
		pthread_mutex_lock(&(r->alleat_lock));
		if (i == r->num_philo)
		{
			printf("EVERYONE ATE!\n");
			r->all_ate = true;
		}
		pthread_mutex_unlock(&(r->alleat_lock));
	}
}

void	p_eat(t_philo *philo)
{
	t_data *rules;

	rules = philo->data;
	pthread_mutex_lock(&(rules->fork[philo->l_fork]));
	action_print(rules, philo->id, FORK);
	if (rules->num_philo == 1)
	{
		sleeper(rules, rules->time_die);
		pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
		return ;
	}
	pthread_mutex_lock(&(rules->fork[philo->r_fork]));
	action_print(rules, philo->id, FORK);
	pthread_mutex_lock(&(rules->meal_lock));
	action_print(rules, philo->id, EAT);
	philo->t_last_meal = current_timestamp();
	(philo->meal_ate)++;
	if (rules->num_eat_flag)
		if (philo->meal_ate == rules->num_eat)
		{
			philo->full = true;
			//printf("%d is full\n", philo->id);
		}
	pthread_mutex_unlock(&(rules->meal_lock));
	sleeper(rules, rules->time_eat);
	pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
	pthread_mutex_unlock(&(rules->fork[philo->r_fork]));
}

//void	p_eat(t_philo *philo)
//{
//	t_data *rules;

//	rules = philo->data;
//	if (pthread_mutex_lock(&(rules->fork[philo->l_fork])))
//		error_msg(ERR_MX);
//	action_print(rules, philo->id, FORK);
//	if (rules->num_philo == 1)
//	{
//		sleeper(rules, rules->time_die);
//		pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
//		return ;
//	}
//	if (pthread_mutex_lock(&(rules->fork[philo->r_fork])))
//		error_msg(ERR_MX);
//	action_print(rules, philo->id, FORK);
//	if (pthread_mutex_lock(&(rules->meal_lock)))
//		error_msg(ERR_MX);
//	action_print(rules, philo->id, EAT);
//	philo->t_last_meal = current_timestamp();
//	if (pthread_mutex_unlock(&(rules->meal_lock)))
//		error_msg(ERR_MX);
//	sleeper(rules, rules->time_eat);
//	(philo->meal_ate)++;
//	if (pthread_mutex_unlock(&(rules->fork[philo->l_fork])))
//		error_msg(ERR_MX);
//	if (pthread_mutex_unlock(&(rules->fork[philo->r_fork])))
//		error_msg(ERR_MX);
//}
void	*p_day(void *void_philo)
{
	t_philo		*philo;
	t_data		*rules;

	philo = (t_philo *)void_philo;
	rules = philo->data;
	if (philo->id % 2)
		usleep((rules->time_sleep)/2);
	//while (!(rules->dead_flag) && !(rules->all_ate))
	while (philo->dead == false && philo->full == false)
	{
		p_eat(philo);
		//if (rules->all_ate == true)
		//{
		//	printf("id: %d everyone ate!\n", philo->id);
		//	break ;
		//}
		action_print(rules, philo->id, SLEEP); // they sleep first
		sleeper(rules, rules->time_sleep);
		action_print(rules, philo->id, THINK); //they think
	}
	return(NULL);
}
void	end_rountine(t_data *r, t_philo *p)
{
	int i;

	i = -1;
	while (++i < r->num_philo)
	{
		if(pthread_join(p[i].thread, NULL))
			error_msg("thread failed");
	}
	i = -1;
	while (++i < r->num_philo)
		pthread_mutex_destroy(&(r->fork[i]));
	pthread_mutex_destroy(&(r->write_lock));
}

int	philo_rountine(t_data *rules)
{
	int 		i;
	//pthread_t	watch;
	t_philo 	*philo;

	i = 0;
	philo = rules->philo;
	rules->start_time = current_timestamp();
	//if (pthread_create(&watch, NULL, &watcher, &rules))
	//	error_msg("Watcher Thread");
	while (i < rules->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &p_day, &(philo[i])))
			error_msg("No thread today"); // clear everything
		philo[i].t_last_meal = current_timestamp();
		i++;
	}
	//if (pthread_join(watch, NULL))
	//	error_msg("watcher join fail");
	//i = 0;
	//while (i < rules->num_philo)
	//{
	//	if (pthread_join(philo[i].thread, NULL))
	//		error_msg("join failed");
	//	i++;
	//}
	death_checker(rules, rules->philo); // monitor death and num_eat
	end_rountine(rules, philo); 
	// need to destroy all the mutex ?
	return (0);
}
