/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:46:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/12 16:58:09 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//	Let's kill da ho.... BEEEECH

int	porkiller(t_main *control, int error)
{
	int	i;

	i = 0;
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
	sem_close(control->sem);
	sem_close(control->sem_print);
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
			break ;
		}
	}
	if (!n)
		printf("ALL PHILOS ARE FULL\n");
	sem_close(control->sem_print);
	sem_close(control->sem_alive);
	sem_close(control->sem);
	return (0);
}

int	main(int argv, char	**argc)
{
	t_main	control;
	int		pro;

	write(1, "\n", 1);
	write(1, PHIL, ft_strlen(PHIL));
	write(1, PROCS, ft_strlen(PROCS));
	write(1, "\n", 1);
	msleep(1250);
	if (!((argv - 1 == 5 || argv - 1 == 4) && init_main(&control, argc)))
		return (printf(RED"ERROR ARGUMENT\n"OFF) * 0 + 1);
	pro = create_process(&control);
	if ((!pro))
		return (porkiller(&control, 1));
	if (pro == 2)
		philo_routine(&control.philo);
	if (pro == 1)
		return (controller(&control));
	return (0);
}
