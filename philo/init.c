/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:38:07 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/05 02:57:52 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_main *control)
{
	int i;

	i = 0;
	control->threads = ft_calloc(control->n_philos, sizeof(pthread_t));
	if (!control->threads)
		return (0);
	while (i < control->n_philos)
	{
		if (pthread_create(&control->threads[i], NULL, \
							philo_routine ,&control->philos[i]))
		{
			free(control->threads);
			free(control->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

static void		init_philo(t_main *control, t_philo *philo, int id)
{
	philo->die_time = control->die_time;
	philo->eat_count = 0;
	philo->eat_max = control->eat_max;
	philo->eat_time = control->eat_time;
	philo->id = id;
	philo->sleep_time = control->sleep_time;
	philo->status = THINKING;
	philo->mutex = &control->mutex;
	philo->the_fork = &control->the_fork;
}

int		init_main(t_main *control, char	**argc)
{
	int	i;

	if (!is_integer(argc[1]))
		return (0);
	control->n_philos = ft_atoi(argc[1]);
	control->die_time = ft_latoi(argc[2]);
	control->eat_time = ft_latoi(argc[3]);
	control->sleep_time = ft_latoi(argc[4]);
	control->the_fork = 1;
	if (argc[5])
		control->eat_max =  ft_latoi(argc[5]);
	else
		control->eat_max = -1;
	i = 0;
	if (pthread_mutex_init(&control->mutex, NULL))
		return(0);
	control->philos = ft_calloc(control->n_philos, sizeof(t_philo));
	if (!control->philos)
		return (0);
	while (i < control->n_philos)
	{
		init_philo(control, &control->philos[i], i);
		i++;
	}
	return (1);
}
