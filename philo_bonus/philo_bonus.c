/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:46:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/08 19:26:57 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	porkiller(t_main *control, int error)
{
	int	i;

	i = 0;
	sem_close(control->sem);
	if (error)
		printf("ERROR PROCESS \n");
	if (control->pid_philo)
	{
		while (i < control->n_philos)
		{
			if (control->pid_philo[i])
				kill(control->pid_philo[i], SIGINT);
			i++;
		}
	}
	return (1);
}

int	controller(t_main *control)
{
	int	n;
	int	status;

	n = control->n_philos;
	while (n)
	{
		wait(&status);
		if (!status)
			n--;
		else
			porkiller(control, 0);
	}
	sem_close(control->sem_print);
	sem_close(control->sem);
	return (0);
}

int	main(int argv, char	**argc)
{
	t_main	control;
	int		pro;

	if (!((argv - 1 == 5 || argv - 1 == 4) && init_main(&control, argc)))
		return (printf("ERROR ARGUMENT\n") * 0 + 1);
	pro = create_process(&control);
	if ((!pro))
		return (porkiller(&control, 1));
	if (pro == 2)
		philo_routine(&control.philo);
	if (pro == 1)
		return (controller(&control));
	return (0);
}
