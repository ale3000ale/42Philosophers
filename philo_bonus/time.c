/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:56:17 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/09 01:55:40 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	msleep(int ms)
{
	struct timeval	time;
	suseconds_t		time_start;
	time_t			sec;
	long			wait_time;

	wait_time = (ms * 1000) / 2;
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

int	timestamp(t_philo *philo, char *s, int alive)
{
	long	local_time;
	long	global_time;

	sem_wait(philo->sem_print);
	local_time = timepassed_ms(philo->time);
	global_time = timepassed_ms(*philo->global_time);
	printf("G:%6ld ms L:%6ld ms, %4d %s\n"OFF, \
		global_time, local_time, philo->id, s);
	write(1,OFF,4);
	if (!alive)
		return (0);
	sem_post(philo->sem_print);
	return (0);
}
