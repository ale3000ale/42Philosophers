/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:33:38 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/09 14:59:10 by amarcell         ###   ########.fr       */
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
