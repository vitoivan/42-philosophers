/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/17 09:41:07 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	eat(t_philo *philo)
{
	if (print_action(philo, EAT))
	{
		fold_forks(philo);
		return (1);
	}
	else
	{
		usleep(philo->ctx->time_to_eat * 1000);
		philo->last_eat = get_time();
		philo->eat_count++;
	}
	return (0);
}
