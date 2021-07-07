/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:04:29 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/07 19:31:52 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_threads(t_main *control)
{
	int	i;

	i = 0;
	gettimeofday(&control->time, NULL);
	control->threads = ft_calloc(control->n_philos, sizeof(pthread_t));
	if (!control->threads)
		return (0);
	while (i < control->n_philos)
	{
		control->philos[i].global_time = &control->time;
		if (pthread_create(&control->threads[i], NULL, \
							philo_routine, &control->philos[i]))
		{
			free(control->threads);
			free(control->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	init_philo(t_main *control, t_philo *philo, int id)
{
	philo->die_time = control->die_time;
	philo->eat_count = 0;
	philo->eat_max = control->eat_max;
	philo->eat_time = control->eat_time;
	philo->id = id;
	philo->sleep_time = control->sleep_time;
	philo->status = THINKING;
	philo->can_i_eat = 0;
}

int	init_main(t_main *control, char	**argc)
{
	if (!is_integer(argc[1]))
		return (0);
	control->n_philos = ft_atoi(argc[1]);
	control->die_time = ft_latoi(argc[2]);
	control->eat_time = ft_latoi(argc[3]);
	control->sleep_time = ft_latoi(argc[4]);
	if (argc[5])
		control->eat_max = ft_latoi(argc[5]);
	else
		control->eat_max = -1;
	init_philo(control, &control->philo, 1);
	if (sem_init(&control->sem, 0, control->n_philos))
		return (0);
	control->philo.sem = control->sem;
	return (1);
}
