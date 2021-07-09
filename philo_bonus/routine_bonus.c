/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:01:10 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/09 01:58:05 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	sleeping(t_philo *philo)
{
	timestamp(philo, SLEEP_STAMP, 1);
	if (sleep_spleeping(philo) < 0)
		return ;
	philo->status = THINKING;
	timestamp(philo, THINKING_STAMP, 1);
}

static int	eating(t_philo *philo)
{
	pthread_join(philo->thread, NULL);
	philo->thread = 0;
	timestamp(philo, EATING_STAMP, 1);
	gettimeofday(&philo->time, NULL);
	if (sleep_eat(philo) < 0)
		return (0);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	philo->can_i_eat = 0;
	timestamp(philo, DROP_STAMP, 1);
	philo->status = SLEEPING;
	if (philo->eat_max != -1 && ++philo->eat_count == philo->eat_max)
	{
		philo->status = FULL;
		return (1);
	}
	return (0);
}

void	philo_routine(t_philo *philo)
{
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2)
		usleep(200);
	while (1)
	{
		if (philo->status == THINKING && !philo->thread)
			pthread_create(&philo->thread, NULL, wait_forks, (void *)philo);
		if (philo->status == EATING)
			if (eating(philo))
				break ;
		if (philo->status == SLEEPING)
			sleeping(philo);
		if (timepassed_ms(philo->time) >= philo->die_time)
			exit(starvation(philo));
	}
	timestamp(philo, FULL_STAMP, 1);
	exit (0);
}
