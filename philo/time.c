/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 03:15:22 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/05 03:20:52 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timepassed_ms(struct timeval time_start)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec * 1000000 + time_now.tv_usec) - \
		(time_start.tv_sec *  1000000 + time_start.tv_usec));
}