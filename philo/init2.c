/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:36:10 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/06 19:04:54 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_set_forks(t_main *control, t_philo *philo)
{
	philo->the_fork_left = &control->the_fork[philo->id % control->n_philos];
	philo->mutex_left = &control->mutex[philo->id % control->n_philos];
	philo->the_fork_rigth = &control->the_fork[philo->id - 1];
	philo->mutex_rigth = &control->mutex[philo->id - 1];
	printf("M %p F %p | %d | F %p M %p\n", philo->mutex_left, philo->the_fork_left, philo->id,\
		philo->the_fork_rigth, philo->mutex_rigth);
}

static int	forks_gen(t_main *control)
{
	int	i;

	i = 0;
	control->the_fork = ft_calloc(control->n_philos, sizeof(int));
	if (!control->the_fork)
	{
		free(control->philos);
		return (0);
	}
	while (i < control->n_philos)
	{
		control->the_fork[i] = 1;
		i++;
	}
	return (1);
}

int	mutex_init(t_main *control)
{
	int	i;

	if (pthread_mutex_init(&control->print_mutex, NULL))
		return (0);
	if (!forks_gen(control))
		return (0);
	i = 0;
	control->mutex = ft_calloc(control->n_philos, sizeof(pthread_mutex_t));
	while (i < control->n_philos)
	{
		if (pthread_mutex_init(&control->mutex[i], NULL))
		{
			free(control->mutex);
			free(control->the_fork);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < control->n_philos)
	{
		philo_set_forks(control, &control->philos[i]);
		i++;
	}
	return (1);
}
