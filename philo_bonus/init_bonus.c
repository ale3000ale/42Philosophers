/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 19:04:29 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/08 19:37:20 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_main *control)
{
	int	i;
	int	pid;

	i = 0;
	while (i < control->n_philos)
	{
		pid = fork();
		control->philo.id = i + 1;
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
	philo->thread = 0;
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
	control->sem = sem_open("forks", control->n_philos, 0660, 0);
	control->sem_print = sem_open("print", 1,  0660, 0);
	if (!control->sem || !control->sem_print)
		return (0);
	control->philo.sem_forks = control->sem;
	control->philo.sem_print = control->sem_print;
	control->pid_philo = ft_calloc(control->n_philos, sizeof(pid_t));
	return (1);
}
