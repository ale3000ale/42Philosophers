/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:38:07 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/10 15:47:25 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thjoin(t_main *control)
{
	int	i;

	i = -1;
	while (++i < control->n_philos)
		pthread_join(control->threads[i], NULL);
}

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
			pthread_mutex_lock(&control->mutex_alive);
			control->stop = 1;
			pthread_mutex_unlock(&control->mutex_alive);
			thjoin(control);
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
	philo->id = id + 1;
	philo->sleep_time = control->sleep_time;
	philo->status = THINKING;
	philo->can_i_eat = 0;
	philo->stop = &control->stop;
	philo->mutex_print = &control->print_mutex;
}

static int	init_args(t_main *control, char **argc)
{
	if (!is_integer(argc[1]) || !is_integer(argc[2]) || !is_integer(argc[3]) \
	 || !is_integer(argc[4]))
		return (0);
	control->n_philos = ft_atoi(argc[1]);
	control->die_time = ft_latoi(argc[2]);
	control->eat_time = ft_latoi(argc[3]);
	control->sleep_time = ft_latoi(argc[4]);
	control->stop = 0;
	if (argc[5])
	{
		if (!is_integer(argc[5]))
			return (0);
		control->eat_max = ft_latoi(argc[5]);
		if (control->eat_max < 1)
			return (0);
	}
	else
		control->eat_max = -1;
	return (control->n_philos > 0 && control->die_time > 0 \
	 && control->eat_time > 0 && control->sleep_time > 0);
}

int	init_main(t_main *control, char **argc)
{
	int	i;

	if (!init_args(control, argc))
		return (0);
	i = -1;
	control->philos = ft_calloc(control->n_philos, sizeof(t_philo));
	if (!control->philos)
		return (0);
	while (++i < control->n_philos)
		init_philo(control, &control->philos[i], i);
	if (!mutex_init(control))
		return (0);
	return (1);
}
