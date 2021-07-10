/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:56:57 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/10 15:39:29 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleep_eat(t_philo *philo)
{
	long			waiting;
	long			extra;

	waiting = philo->eat_time;
	extra = timepassed_ms(philo->time);
	if (waiting - extra < philo->die_time)
		return (msleep(philo->eat_time - extra));
	else
	{
		msleep(philo->die_time - extra);
		return (-1);
	}
	return (1);
}

static void	eating(t_philo *philo)
{
	timestamp(philo, EATING_STAMP);
	gettimeofday(&philo->time, NULL);
	if (sleep_eat(philo) < 0)
		return ;
	timestamp(philo, DROP_STAMP);
	pthread_mutex_lock(philo->mutex_left);
	philo->the_fork_left[0] = 1;
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_lock(philo->mutex_rigth);
	philo->the_fork_rigth[0] = 1;
	pthread_mutex_unlock(philo->mutex_rigth);
	philo->can_i_eat = 0;
}

static int	try_left_eat(t_philo *philo)
{
	if (get_fork(philo, philo->mutex_left, philo->the_fork_left) \
		 && philo->can_i_eat == 2)
		philo->status = EATING;
	return (0);
}

static int	try_rigth_eat(t_philo *philo)
{
	if (get_fork(philo, philo->mutex_rigth, philo->the_fork_rigth) \
		 && philo->can_i_eat == 2)
		philo->status = EATING;
	return (0);
}

int	think_time(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_alive);
	if (*philo->stop)
		return (pthread_mutex_unlock(philo->mutex_alive) * 0);
	pthread_mutex_unlock(philo->mutex_alive);
	try_left_eat(philo);
	try_rigth_eat(philo);
	if (philo->status == EATING)
	{
		eating(philo);
		philo->eat_count++;
		philo->status = SLEEPING;
		if (philo->eat_max != -1 && philo->eat_count == philo->eat_max)
		{
			philo->status = FULL;
			return (1);
		}
	}
	return (0);
}
