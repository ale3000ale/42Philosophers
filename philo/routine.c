/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:28:01 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/07 03:12:26 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	sleep_spleeping(t_philo *philo)
{
	long			waiting;
	long			extra;

	waiting = timepassed_ms(philo->time) + philo->sleep_time;
	extra = waiting - philo->eat_time - philo->sleep_time;
	if (waiting < philo->die_time)
		return (msleep(philo->sleep_time - extra));
		//return (printf("%d WAITSLEEP %ld sleep %ld\n", philo->id, waiting, msleep(waiting - philo->die_time)));
	else
	{
		msleep(philo->die_time - philo->eat_time - extra);
		//printf(" %d WAITDEAD %ld sleep %ld\n", philo->id, waiting, msleep(waiting - philo->die_time));
		return (-1);
	}
	/*
	while (timepassed_ms(time_start) < philo->sleep_time)
	{
		sleep(2);
		if (timepassed_ms(philo->time) > philo->die_time)
			return (-1);
	}*/
	return (1);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_print);
	printf("G:%8ld ms L:%8ld ms, %4d is sleeping "PUR"(( _ _ ))"CYAN"..zzZZ \n"\
		OFF, timepassed_ms(*philo->global_time), timepassed_ms(philo->time), philo->id);
	pthread_mutex_unlock(philo->mutex_print);
	if (sleep_spleeping(philo) < 0)
		return ;
	philo->status = THINKING;
	pthread_mutex_lock(philo->mutex_print);
	printf("G:%8ld ms L:%8ld ms, %4d is thinking "PUR"('ω')"GREEN"｡o○ \n"OFF, \
		timepassed_ms(*philo->global_time), timepassed_ms(philo->time), philo->id);
	pthread_mutex_unlock(philo->mutex_print);
}

void	*deathing(t_philo *philo)
{
	philo->status = DEAD;
	pthread_mutex_lock(philo->mutex_print);
	printf("G:%8ld ms L:%8ld ms, %4d died "PUR"(´"RED"༎ຶོ"PUR"ρ"RED"༎ຶོ"PUR"`)\n" \
	OFF, timepassed_ms(*philo->global_time), timepassed_ms(philo->time), philo->id);
	return (0);
}

void	*philo_routine(void	*ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if (*philo->stop)
			return (0);
		if (timepassed_ms(philo->time) >= philo->die_time && !*philo->stop)
			return (deathing(philo));
		else if (philo->status == THINKING && !*philo->stop)
			if (think_time(philo))
				break ;
		if (philo->status == SLEEPING && !*philo->stop)
			sleeping(philo);
	}
	pthread_mutex_lock(philo->mutex_print);
	printf("%8ld ms, %4d are FULL "PUR"("YEL"●"PUR"´ω｀" \
	YEL"●"PUR")\n"OFF, timepassed_ms(*philo->global_time), philo->id);
	pthread_mutex_unlock(philo->mutex_print);
	return (0);
}
