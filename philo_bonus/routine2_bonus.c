/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:07:07 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/09 01:58:15 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_forks(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	sem_wait(philo->sem_forks);
	philo->can_i_eat++;
	timestamp(philo, FORK_STAMP, 1);
	sem_wait(philo->sem_forks);
	philo->can_i_eat++;
	timestamp(philo, FORK_STAMP, 1);
	philo->status = EATING;
	return (0);
}

int	starvation(t_philo *philo)
{
	philo->status = DEAD;
	timestamp(philo, DEAD_STAMP, 0);
	if (philo->thread)
		pthread_detach(philo->thread);
	while (philo->can_i_eat)
	{
		sem_post(philo->sem_forks);
		philo->can_i_eat--;
	}
	return (1);
}
