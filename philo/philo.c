/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 18:11:30 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/06 16:51:51 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thdetach(t_main *control)
{
	int	i;

	i = 0;
	while (i < control->n_philos)
	{
		pthread_detach(control->threads[i]);
		i++;
	}
}

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
	free(control->mutex);
}

static void	controller(t_main *control)
{
	int		remaining;
	int		i;

	i = 0;
	remaining = control->n_philos;
	while (1)
	{	
		i = i % control->n_philos;
		if (control->philos[i].status == DEAD)
		{
			control->stop = 1;
			thdetach(control);
			break ;
		}
		else if (control->philos[i].status == FULL)
		{
			remaining--;
			control->philos[i].status = FINISH;
		}
		if (!remaining)
			break ;
		i++;
	}
	return ;
}

int	main(int argv, char	**argc)
{
	t_main	control;

	if (!((argv - 1 == 5 || argv - 1 == 4) && init_main(&control, argc)))
		return (printf("ERROR ARGUMENT\n") * 0 + 1);
	if ((!create_threads(&control)))
		return (printf("ERROR THREADS \n") * 0 + 1);
	controller(&control);
	free(control.threads);
	free(control.philos);
	destoy_mutex(&control);
	return (0);
}
