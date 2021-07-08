/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:46:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/08 02:11:26 by alexmarcell      ###   ########.fr       */
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
				kill(control->pid_philo[i], SIGKILL);
			i++;
		}
	}
	return (1);
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
		printf("PHILOS %d\n", control.philo.id);
	if (pro == 1)
		//ck
	return (1);
}
