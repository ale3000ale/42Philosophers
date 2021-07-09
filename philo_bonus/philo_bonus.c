/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:46:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/09 02:40:00 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//	Let's kill da ho.... BEEEECH

int	porkiller(t_main *control, int error)
{
	int	i;

	i = 0;
	sem_close(control->sem);
	if (error)
		printf(RED"ERROR PROCESS \n"OFF);
	if (control->pid_philo)
	{
		while (i < control->n_philos)
		{
			if (control->pid_philo[i])
				kill(control->pid_philo[i], SIGKILL);
			i++;
		}
	}
	if (error)
		return (1);
	return (0);
}

//	

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
		{
			porkiller(control, 0);
			break;
		}
			
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
		return (printf(RED"ERROR ARGUMENT\n"OFF) * 0 + 1);
	write(1, "\n", 1);
	write(1, PHIL, ft_strlen(PHIL));
	write(1, PROCS, ft_strlen(PHIL));
	msleep(2000);
	pro = create_process(&control);
	if ((!pro))
		return (porkiller(&control, 1));
	if (pro == 2)
		philo_routine(&control.philo);
	if (pro == 1)
		return (controller(&control));
	return (0);
}
