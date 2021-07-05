/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 18:11:30 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/05 19:23:23 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thdetach(t_main *control)
{
	int	i;

	i = 0;
	while (i < control->n_philos)
	{
		pthread_detach(control->threads[i]);
		i++;
	}
}

int	main(int argv, char	**argc)
{
	t_main	control;
	int		i;
	int		remaining;

	if (!((argv - 1 == 5 || argv - 1 == 4) && init_main(&control, argc)))
		return (printf("ERROR ARGUMENT\n") * 0 + 1);
	if ((!create_threads(&control)))
		return (printf("ERROR THREADS \n") * 0 + 1);
	i = 0;
	remaining = control.n_philos;
	while (1)
	{	
		i = i % control.n_philos;
		if (control.philos[i].status == DEAD)
		{
			control.stop = 1;
			thdetach(&control);
			break ;
		}
		else if (control.philos[i].status == FULL)
		{
			remaining--;
			control.philos[i].status = FINISH;
		}
		if (!remaining)
			break ;
		i++;
	}
	free(control.threads);
	free(control.philos);
	pthread_mutex_destroy(&control.mutex);
	return (0);
}
