/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 18:11:30 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/10 15:53:06 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destoy_mutex(t_main *control)
{
	int	i;

	pthread_mutex_destroy(&control->print_mutex);
	i = 0;
	while (i < control->n_philos)
	{
		pthread_mutex_destroy(&control->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&control->print_mutex);
	pthread_mutex_destroy(&control->mutex_alive);
	free(control->mutex);
}

static int	controller(t_main *control)
{
	int		remaining;
	int		i;

	i = 0;
	remaining = control->n_philos;
	while (1)
	{	
		i = i % control->n_philos;
		pthread_mutex_lock(&control->mutex_alive);
		if (control->stop == 1)
			return (pthread_mutex_unlock(&control->mutex_alive));
		pthread_mutex_unlock(&control->mutex_alive);
		if (control->philos[i].status == FULL)
		{
			remaining--;
			control->philos[i].status = FINISH;
		}
		if (!remaining)
			return (1);
		i++;
	}
	return (1);
}

int	main(int argv, char	**argc)
{
	t_main	control;

	write(1, "\n", 1);
	write(1, PHIL, ft_strlen(PHIL));
	write(1, THR, ft_strlen(THR));
	write(1, "\n", 1);
	msleep(1250);
	if (!((argv - 1 == 5 || argv - 1 == 4) && init_main(&control, argc)))
		return (printf(RED"ERROR ARGUMENT\n"OFF) * 0 + 1);
	if ((!create_threads(&control)))
		return (printf(RED"ERROR THREADS \n"OFF) * 0 + 1);
	if (!controller(&control))
		thjoin(&control);
	else
		printf("ALL ARE FULL\n");
	free(control.threads);
	free(control.philos);
	free(control.the_fork);
	destoy_mutex(&control);
	return (0);
}
