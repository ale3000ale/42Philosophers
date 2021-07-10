/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:07:07 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/10 16:10:44 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_forks(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	sem_wait(philo->sem_forks);
	philo->can_i_eat++;
	timestamp(philo, FORK_STAMP);
	sem_wait(philo->sem_forks);
	philo->can_i_eat++;
	timestamp(philo, FORK_STAMP);
	philo->status = EATING;
	return (0);
}

int	starvation(t_philo *philo)
{
	philo->status = DEAD;
	timestamp(philo, DEAD_STAMP);
	if (philo->thread)
		pthread_detach(philo->thread);
	while (philo->can_i_eat)
	{
		sem_post(philo->sem_forks);
		philo->can_i_eat--;
	}
	return (1);
}
