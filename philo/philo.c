/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 18:11:30 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/05 03:30:32 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thkill(t_main *control)
{
	int i;

	i = 0;
	while (i < control->n_philos)
	{
		pthread_kill(control->threads[i], 0);
		i++;
	}
	free(control->threads);
	free(control->philos);
}

int	eating(t_philo *philo)
{
	if (philo->the_fork[0])
	{
		pthread_mutex_lock(philo->mutex);
		philo->the_fork[0] = 0;
		printf("%d eating at: %ld\n", philo->id, timepassed_ms(philo->time));
		sleep(2);
		philo->the_fork[0] = 1;
		pthread_mutex_unlock(philo->mutex);
		return(1);
	}
	return(0);
}

void	*philo_routine(void	*ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	gettimeofday(&philo->time, NULL);
	while (1)
	{
		if (timepassed_ms(philo->time) >= philo->die_time)
		{
			philo->status = DEAD;
			return (0);
		}
		if (philo->status == THINKING)
		{
			if (eating(philo))
			{
				gettimeofday(&philo->time, NULL);
				philo->eat_count++;
				if (philo->eat_max != -1 && philo->eat_count == philo->eat_max)
				{
					philo->status = FULL;
					break ;
				}
				philo->status = SLEEPING;
			}
		}
		if (philo->status == SLEEPING)
		{
			printf("%d sleep time at: %ld\n", philo->id, timepassed_ms(philo->time));
			msleep(philo->sleep_time);
			philo->status = THINKING;
			gettimeofday(&philo->time, NULL);
			printf("%d thinking time at: %ld\n", philo->id, timepassed_ms(philo->time));
		}
	}
	printf("%d are FULL at: %ld\n", philo->id, timepassed_ms(philo->time));
	return(0);
}

int main(int argv, char	**argc)
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
			thkill(&control);
			return (printf("phil %d dead\n", i));
		}
		if (control.philos[i].status == FULL)
		{
			remaining--;
			control.philos[i].status = FINISH;
			printf("remaing: %d\n",remaining);
		}
		if (!remaining)
			break ;
		i++;
	}
	free(control.threads);
	free(control.philos);
	printf("FINISH\n");
	return(0);
}