/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 03:15:22 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/10 15:42:03 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	msleep(int ms)
{
	struct timeval	time;
	suseconds_t		time_start;
	time_t			sec;
	long			wait_time;

	wait_time = (ms * 1000) >> 1;
	ms = ms * 1000;
	gettimeofday(&time, NULL);
	time_start = time.tv_usec;
	sec = time.tv_sec * 1000000 + time_start;
	while ((time.tv_sec * 1000000 + time.tv_usec) - \
		(sec) < ms)
	{
		usleep(wait_time);
		wait_time = wait_time >> 2;
		gettimeofday(&time, NULL);
	}
	return (((time.tv_sec * 1000000 + time.tv_usec) - \
		(sec)) / 1000);
}

long	timepassed_ms(struct timeval time_start)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (((time_now.tv_sec * 1000000 + time_now.tv_usec) - \
		(time_start.tv_sec * 1000000 + time_start.tv_usec)) / 1000);
}

int	timestamp(t_philo *philo, char *s)
{
	long	global_time;

	pthread_mutex_lock(philo->mutex_alive);
	if (*philo->stop)
		return (pthread_mutex_unlock(philo->mutex_alive) * 0);
	if (philo->status == DEAD)
		*philo->stop = 1;
	pthread_mutex_unlock(philo->mutex_alive);
	pthread_mutex_lock(philo->mutex_print);
	global_time = timepassed_ms(*philo->global_time);
	printf("G:%6ld ms | %4d %s\n"\
		OFF, global_time, philo->id, s);
	pthread_mutex_unlock(philo->mutex_print);
	return (0);
}
