/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:33:38 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/05 02:38:45 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (i == 0 && !(ft_isdigit(s[i]) && s[i] != '-'))
			return (0);
		if(!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return(1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int is_integer(char *s)
{
	long	num;

	if (ft_strlen(s) - (s[0] == '-') > 10)
		return (0);
	if (!ft_isnumber(s))
		return (0);
	num = ft_latoi(s);
	if (num > INT32_MAX || num < INT32_MIN)
		return (0);
	return (1);
}

long	msleep(int ms)
{
	struct timeval	time;
	suseconds_t	time_start;
	time_t		sec;
	long		wait_time;

	wait_time = (ms * 1000) / 2;
	gettimeofday(&time, NULL);
	time_start = time.tv_usec;
	sec = time.tv_sec;
	while ((time.tv_sec * 1000000 + time.tv_usec) - \
		(sec *  1000000 + time_start) < ms * 1000)
	{
		usleep(wait_time);
		gettimeofday(&time, NULL);
		wait_time /= 4;
	}
	/*printf("wait: %ld\nms: %d = %ld\n", wait_time, (ms * 1000), (time.tv_sec * 1000000 + time.tv_usec) - \
		(sec *  1000000 + time_start));*/
	return (((time.tv_sec * 1000000 + time.tv_usec) - \
		(sec *  1000000 + time_start)) / 1000);
}
