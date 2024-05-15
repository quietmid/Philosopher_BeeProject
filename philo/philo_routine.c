/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:43:42 by jlu               #+#    #+#             */
/*   Updated: 2024/05/15 18:37:59 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_time_checker(t_data *r, t_philo *p)
{
	// pthread_mutex_lock(&(r->p_lock));
	pthread_mutex_lock(&(r->meal_lock));
	if (time_diff(p->t_last_meal, current_timestamp()) > r->time_die)
	{
		p->dead = true;
		pthread_mutex_unlock(&(r->meal_lock));
		action_print(r, p->id, DEATH);
		return (1);
	}
	pthread_mutex_unlock(&(r->meal_lock));
	// pthread_mutex_unlock(&(r->p_lock));
	return (0);
}
void	death_checker(t_data *r, t_philo *p)
{
	while (1)
	{
		//printf("here\n");
		usleep(150);
		if (allp_ate(r, p))
			break ;
		if (philo_dead(r, p))
			break ;
	}
}
// need to create two more functions for allp_ate and philo_dead
//void	death_checker(t_data *r, t_philo *p)
//{
//	int i;

//	// printf("death_checker in\n"); // debugg
//	while (!is_exit(r))
//	{
//		usleep(150);
//		if (r->num_eat_flag)
//		{
//			// printf("Number of Eat flag on!\n"); //debugg
//			i = -1;
//			while (++i < r->num_philo && p_is_full(&p[i], r))
//				;
//			if (i == r->num_philo)
//			{
//				pthread_mutex_lock(&(r->dead_lock));
//				r->exit = true;
//				pthread_mutex_unlock(&(r->dead_lock));
//				// break ;
//			}
//		}
//		i = -1;
//		while (++i < r->num_philo) 
//		{	
//			pthread_mutex_lock(&(r->dead_lock));
//			r->exit = meal_time_checker(r, p);
//			pthread_mutex_unlock(&(r->dead_lock));
//		 	if (is_exit(r))
//		 	{
//		 		printf("here\n");
//		 		break ;
//		 	}
//		}
//	}
//}
// void	death_checker(t_data *r, t_philo *p)
// {
// 	int i;

// 	while (!is_full(r))
// 	{
// 		i = -1;
// 		if (r->num_eat_flag)
// 		{
// 			while (++i < r->num_philo && p_is_full(&p[i], r))
// 				;
// 			if (i == r->num_philo)
// 			{
// 				pthread_mutex_lock(&(r->dead_lock));
// 				r->all_ate = true;
// 				pthread_mutex_unlock(&(r->dead_lock));
// 			}
// 		}
// 		i = -1;
// 		while (++i < r->num_philo && !is_dead(r)) // here I believe it is because I m using the deadlock to check the while loop but also using the deadlock inside this while loop.
// 		{
// 				pthread_mutex_lock(&(r->dead_lock));
// 				r->dead_flag = meal_time_checker(r, p);
// 				pthread_mutex_unlock(&(r->dead_lock));
// 				// usleep(150);
// 		}
// 		if (is_dead(r))
// 			break ;
// 	}
// }
int	p_eat(t_philo *p)
{
	t_data *r;

	r = p->data;
	if (is_exit(r) || p_is_dead(p, r))
		return (1);
	pthread_mutex_lock(&(r->fork[p->l_fork]));
	p->fork_l = true;
	action_print(r, p->id, FORK);
	if (r->num_philo == 1)
	{
		put_downforks(&(r->fork[p->l_fork]), &(r->fork[p->r_fork]), p);
		return (1);
	}
	pthread_mutex_lock(&(r->fork[p->r_fork]));
	p->fork_r = true;
	action_print(r, p->id, FORK);
	eating(r, p);
	//sleeper(r, r->time_eat);
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
	//long int	sleeptime;

	philo = (t_philo *)void_philo;
	rules = philo->data;
	if (!(philo->id % 2))
	{
		action_print(rules, philo->id, THINK);
		sleeper(rules, (rules->time_sleep)/2);
	}
	while (!p_is_dead(philo, rules) && !is_exit(rules))
	{
		if (p_eat(philo))
			break ; //this way, if its one philo, it end
		sleeping(rules, philo);
		action_print(rules, philo->id, THINK);
	}
	if (is_exit(rules))
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
		pthread_join(philo[i].thread, NULL);
		//if(pthread_join(philo[i].thread, NULL))
			//error_msg("thread failed");
	}
	end_rountine(rules);
	return (0);
}
