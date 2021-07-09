/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:28:01 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/09 19:19:21 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_philo *philo, pthread_mutex_t *mutex, int *fork)
{
	pthread_mutex_lock(mutex);
	if (fork[0])
	{
		fork[0] = 0;
		philo->can_i_eat++;
		timestamp(philo, FORK_STAMP, 1);
		pthread_mutex_unlock(mutex);
		return (1);
	}
	pthread_mutex_unlock(mutex);
	return (0);
}

static long	sleep_spleeping(t_philo *philo)
{
	long			waiting;
	long			extra;

	waiting = timepassed_ms(philo->time) + philo->sleep_time;
	extra = waiting - philo->eat_time - philo->sleep_time;
	if (waiting - extra < philo->die_time)
		return (msleep(philo->sleep_time - extra));
	else
	{
		msleep(philo->die_time - philo->eat_time - extra);
		return (-1);
	}
	return (1);
}

static void	sleeping(t_philo *philo)
{
	timestamp(philo, SLEEP_STAMP, 1);
	if (sleep_spleeping(philo) < 0)
		return ;
	philo->status = THINKING;
	timestamp(philo, THINKING_STAMP, 1);
}

void	*starvation(t_philo *philo)
{
	philo->status = DEAD;
	pthread_mutex_lock(philo->mutex_alive);
	*philo->stop = 1;
	pthread_mutex_unlock(philo->mutex_alive);
	timestamp(philo, DEAD_STAMP, 0);
	return (0);
}

void	*philo_routine(void	*ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(philo->mutex_alive);
		if (*philo->stop)
			return (0);
		pthread_mutex_unlock(philo->mutex_alive);
		if (philo->status == SLEEPING)
			sleeping(philo);
		if (philo->status == THINKING)
			if (think_time(philo))
				break ;
		if (timepassed_ms(philo->time) >= philo->die_time)
			return (starvation(philo));
	}
	timestamp(philo, FULL_STAMP, 1);
	return (0);
}
