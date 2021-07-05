/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 18:14:11 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/05 02:57:42 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

# define	DEAD		0
# define	EATING		1
# define	THINKING	2
# define	SLEEPING	3
# define	FULL		4
# define	FINISH		5

typedef struct	s_philo
{
	int				id;
	int				status;
	int				*the_fork;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			eat_count;
	long			eat_max;
	pthread_mutex_t	*mutex;
	struct timeval	time;
}				t_philo;

typedef struct	s_main
{
	int				n_philos;
	pthread_t		*threads;
	pthread_mutex_t	mutex;
	t_philo			*philos;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			eat_max;
	int				the_fork;
}				t_main;

long	ft_latoi(const char *str);
int		ft_atoi(const char *str);
int		ft_isnumber(char *s);
int		ft_strlen(char *s);
int 	is_integer(char *s);
void	*ft_calloc(size_t count, size_t size);
int		init_main(t_main *control, char	**argc);
long	msleep(int ms);
void	*philo_routine(void	*philo);
int 	create_threads(t_main *control);

#endif