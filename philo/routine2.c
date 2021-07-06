/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:56:57 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/06 18:04:44 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_fork(t_philo *philo, pthread_mutex_t *mutex, int *fork)
{
	pthread_mutex_lock(mutex);
	if (fork[0])
	{
		fork[0]--;
		philo->can_i_eat++;
		pthread_mutex_lock(philo->mutex_print);
		printf("%8ld ms, %4d has taken a fork ", \
			timepassed_ms(*philo->global_time), philo->id);
		printf(PUR"🍴(｀∇´) \n"OFF);
		pthread_mutex_unlock(philo->mutex_print);
		pthread_mutex_unlock(mutex);
		return (1);
	}
	pthread_mutex_unlock(mutex);
	return (0);
}

static void	eating(t_philo *philo)
{
	gettimeofday(&philo->time, NULL);
	pthread_mutex_lock(philo->mutex_print);
	printf("%8ld ms, %4d is eating ", \
		timepassed_ms(*philo->global_time), philo->id);
	printf(PUR"( ^o^)🍝 \n"OFF);
	pthread_mutex_unlock(philo->mutex_print);
	philo->the_fork_left[0]++;
	philo->the_fork_rigth[0]++;
	msleep(philo->eat_time);
	philo->can_i_eat = 0;
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
