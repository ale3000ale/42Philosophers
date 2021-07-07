/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:56:57 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/07 18:32:34 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleep_eat(t_philo *philo)
{
	long			waiting;
	long			extra;

	waiting = timepassed_ms(philo->time) + philo->eat_time;
	extra = waiting - philo->eat_time;
	if (waiting - extra < philo->die_time)
		return (msleep(philo->sleep_time - extra));
	else
	{
		msleep(philo->die_time - extra);
		return (-1);
	}
	return (1);
}

static void	eating(t_philo *philo)
{
	timestamp(philo, EATING_STAMP, 1);
	gettimeofday(&philo->time, NULL);
	if (sleep_eat(philo) < 0)
		return ;
	pthread_mutex_lock(philo->mutex_left);
	philo->the_fork_left[0] = 1;
	pthread_mutex_unlock(philo->mutex_left);
	pthread_mutex_lock(philo->mutex_rigth);
	philo->the_fork_rigth[0] = 1;
	pthread_mutex_unlock(philo->mutex_rigth);
	philo->can_i_eat = 0;
	timestamp(philo, DROP_STAMP, 1);
}

static int	try_left_eat(t_philo *philo)
{
	if (get_fork(philo, philo->mutex_left, philo->the_fork_left) \
		 && philo->can_i_eat == 2)
	{
		eating(philo);
		philo->eat_count++;
		philo->status = SLEEPING;
		if (philo->eat_max != -1 && philo->eat_count == philo->eat_max)
			philo->status = FULL;
		return (1);
	}
	return (0);
}

static int	try_rigth_eat(t_philo *philo)
{
	if (get_fork(philo, philo->mutex_rigth, philo->the_fork_rigth) \
		 && philo->can_i_eat == 2)
	{
		eating(philo);
		philo->eat_count++;
		philo->status = SLEEPING;
		if (philo->eat_max != -1 && philo->eat_count == philo->eat_max)
			philo->status = FULL;
		return (1);
	}
	return (0);
}

int	think_time(t_philo *philo)
{
	if (try_left_eat(philo))
		return (philo->status == FULL);
	if (try_rigth_eat(philo))
		return (philo->status == FULL);
	return (0);
}
