/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:46:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/07 19:08:57 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argv, char	**argc)
{
	t_main	control;

	if (!((argv - 1 == 5 || argv - 1 == 4) && init_main(&control, argc)))
		return (printf("ERROR ARGUMENT\n") * 0 + 1);
	//if ((!create_threads(&control)))
	//	return (printf("ERROR THREADS \n") * 0 + 1);
	return (1);
}
