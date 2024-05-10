/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/05/10 14:23:38 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_time_checker(t_data *r, t_philo *p)
{
	// pthread_mutex_lock(&(r->p_lock));
	pthread_mutex_lock(&(r->meal_lock));
	if (time_diff(p->t_last_meal, current_timestamp()) > r->time_die)
	{
		action_print(r, p->id, DEATH);
		p->dead = true;
		pthread_mutex_unlock(&(r->meal_lock));
		// pthread_mutex_unlock(&(r->p_lock));
		return (1);
	}
	pthread_mutex_unlock(&(r->meal_lock));
	// pthread_mutex_unlock(&(r->p_lock));
	return (0);
}

void	death_checker(t_data *r, t_philo *p)
{
	int i;

	while (!is_full(r))
	{
		i = -1;
		if (r->num_eat_flag)
		{
			while (++i < r->num_philo && p_is_full(&p[i], r))
				;
			if (i == r->num_philo)
			{
				pthread_mutex_lock(&(r->dead_lock));
				r->all_ate = true;
				pthread_mutex_unlock(&(r->dead_lock));
			}
		}
		i = -1;
		while (++i < r->num_philo && !is_dead(r)) // here I believe it is because I m using the deadlock to check the while loop but also using the deadlock inside this while loop.
		{
				pthread_mutex_lock(&(r->dead_lock));
				r->dead_flag = meal_time_checker(r, p);
				pthread_mutex_unlock(&(r->dead_lock));
				// usleep(150);
		}
		if (is_dead(r))
			break ;
	}
}
int	p_eat(t_philo *p)
{
	t_data *r;

	r = p->data;
	pthread_mutex_lock(&(r->fork[p->l_fork]));
	p->fork_l = true;
	action_print(r, p->id, FORK);
	if (r->num_philo == 1)
	{
		sleeper(r, r->time_die);
		put_downforks(&(r->fork[p->l_fork]), &(r->fork[p->r_fork]), p);
		action_print(r, p->id, D_LFORK); // debugg
		return (1);
	}
	pthread_mutex_lock(&(r->fork[p->r_fork]));
	p->fork_r = true;
	action_print(r, p->id, FORK);
	eating(r, p);
	sleeper(r, r->time_eat);
		//debugg
		// pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
		// philo->fork_l = false;
		// action_print(rules, philo->id, D_LFORK);
		// pthread_mutex_unlock(&(rules->fork[philo->r_fork]));
		// philo->fork_r = false;
		// action_print(rules, philo->id, D_RFORK);
		//debugg
	put_downforks(&(r->fork[p->l_fork]), &(r->fork[p->r_fork]), p);
	return (0);
}
// void	p_eat(t_philo *philo)
// {
// 	t_data *rules;

// 	rules = philo->data;
// 	pthread_mutex_lock(&(rules->fork[philo->l_fork]));
// 	philo->fork_l = true;
// 	action_print(rules, philo->id, FORK);
// 	if (rules->num_philo == 1)
// 	{
// 		sleeper(rules, rules->time_die);
// 		pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
// 		philo->fork_l = false;
// 		action_print(rules, philo->id, D_LFORK); // debugg
// 		return ;
// 	}
// 	pthread_mutex_lock(&(rules->fork[philo->r_fork]));
// 	philo->fork_r = true;
// 	action_print(rules, philo->id, FORK);
// 	eating(rules, philo);
// 	sleeper(rules, rules->time_eat);
// 		//debugg
// 		// pthread_mutex_unlock(&(rules->fork[philo->l_fork]));
// 		// philo->fork_l = false;
// 		// action_print(rules, philo->id, D_LFORK);
// 		// pthread_mutex_unlock(&(rules->fork[philo->r_fork]));
// 		// philo->fork_r = false;
// 		// action_print(rules, philo->id, D_RFORK);
// 		//debugg
// 	put_downforks(&(rules->fork[philo->l_fork]), &(rules->fork[philo->r_fork]), philo);
// }

void	*p_day(void *void_philo)
{
	t_philo		*philo;
	t_data		*rules;
	long int	sleeptime;

	philo = (t_philo *)void_philo;
	rules = philo->data;
	if ((rules->time_sleep)/2 < 100)
		sleeptime = 100;
	else
		sleeptime = (rules->time_sleep)/2;
	if (philo->id % 2)
		sleeper(rules, sleeptime);
	while (!p_is_dead(philo, rules) && !is_dead(rules))
	//while (!(p_is_dead(philo)) && !(p_is_full(philo)))
	{
		if (!is_full(rules))
		{
			if (p_eat(philo))
				break ;
			action_print(rules, philo->id, SLEEP);
			sleeper(rules, rules->time_sleep);
			action_print(rules, philo->id, THINK);
		}
		else
			break ;
	}
	all_putdown(rules, philo);
	return (NULL);
}

int	philo_rountine(t_data *rules)
{
	int 		i;
	t_philo 	*philo;

	i = 0;
	philo = rules->philo;
	rules->start_time = current_timestamp();
	while (i < rules->num_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &p_day, &(philo[i])))
			error_msg("No thread today"); // clear everything
		pthread_mutex_lock(&(rules->meal_lock));
		philo[i].t_last_meal = current_timestamp();
		pthread_mutex_unlock(&(rules->meal_lock));
		i++;
	}
	death_checker(rules, rules->philo);
	i = -1;
	while (++i < rules->num_philo)
	{
		if(pthread_join(philo[i].thread, NULL))
			error_msg("thread failed");
	}
	end_rountine(rules);
	return (0);
}
