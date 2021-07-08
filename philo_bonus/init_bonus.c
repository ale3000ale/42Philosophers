/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:04:29 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/08 02:16:58 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_main *control)
{
	int	i;
	int pid;

	i = 0;
	while (i < control->n_philos)
	{
		pid = fork();
		control->philo.id += i;
		if (i > 5)
			printf("AO\n");
		if (!pid)
			return (2);
		if (pid < 0)
			return (0);
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
	philo->global_time = &control->time;
}

int	init_main(t_main *control, char	**argc)
{
	if (!is_integer(argc[1]))
		return (0);
	control->n_philos = ft_atoi(argc[1]);
	control->die_time = ft_latoi(argc[2]);
	control->eat_time = ft_latoi(argc[3]);
	control->sleep_time = ft_latoi(argc[4]);
	gettimeofday(&control->time, NULL);
	if (argc[5])
		control->eat_max = ft_latoi(argc[5]);
	else
		control->eat_max = -1;
	init_philo(control, &control->philo, 1);
	control->sem = sem_open("forks", control->n_philos, O_CREAT);
	if (!control->sem)
		return (0);
	control->philo.sem = control->sem;
	control->pid_philo = ft_calloc(control->n_philos, sizeof(pid_t));
	return (1);
}
