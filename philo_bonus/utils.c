/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:46:44 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/08 02:12:25 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_integer(char *s)
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
