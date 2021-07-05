/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:28:01 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/05 18:24:30 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	printf("%8ld ms, %4d is eating ", \
		timepassed_ms(*philo->global_time), philo->id);
	printf(PUR"( ^o^)🍝 \n"OFF);
	gettimeofday(&philo->time, NULL);
	msleep(philo->eat_time);
	philo->the_fork[0] += 2;
	philo->can_i_eat = 0;
}

static int	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if (philo->the_fork[0])
	{
		philo->the_fork[0]--;
		philo->can_i_eat++;
		printf("%8ld ms, %4d has taken a fork ", \
			timepassed_ms(*philo->global_time), philo->id);
		printf(PUR"🍴(｀∇´)🍴 \n"OFF);
		pthread_mutex_unlock(philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex);
	return (0);
}

static int	think_time(t_philo *philo)
{
	if (get_fork(philo) && philo->can_i_eat == 2)
	{
		eating(philo);
		philo->eat_count++;
		if (philo->eat_max != -1 && philo->eat_count == philo->eat_max)
		{
			philo->status = FULL;
			return (1);
		}
		philo->status = SLEEPING;
	}
	return (0);
}

static void	sleeping(t_philo *philo)
{
	printf("%8ld ms, %4d is sleeping "PUR"(( _ _ ))"CYAN"..zzZZ \n"\
	OFF, timepassed_ms(*philo->global_time), philo->id);
	gettimeofday(&philo->time, NULL);
	msleep(philo->sleep_time);
	philo->status = THINKING;
	printf("%8ld ms, %4d is thinking "PUR"('ω')"GREEN"｡o○ \n"OFF, \
		timepassed_ms(*philo->global_time), philo->id);
	gettimeofday(&philo->time, NULL);
}

void	*deathing(t_philo *philo)
{
	philo->status = DEAD;
	printf("%8ld ms, %4d died "PUR"(´"RED"༎ຶོ"PUR"ρ"RED"༎ຶོ"PUR"`)\n" \
	OFF, timepassed_ms(*philo->global_time), philo->id);
	return (0);
}

void	*philo_routine(void	*ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2)
		usleep(100);
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
	printf("%8ld ms, %4d are FULL "PUR"("YEL"●"PUR"´ω｀" \
	YEL"●"PUR")\n"OFF, timepassed_ms(*philo->global_time), philo->id);
	return (0);
}
