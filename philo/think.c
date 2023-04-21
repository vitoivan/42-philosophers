/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/21 19:47:05 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int get_think_time(t_philo *philo)
{
	int	think_time;
	int	eat_time;
	int	sleep_time;
	int	die_time;

	eat_time = philo->ctx->time_to_eat;
	sleep_time = philo->ctx->time_to_sleep;
	die_time = philo->ctx->time_to_die;
	think_time = (die_time - (eat_time + sleep_time)) / 3;
	if (think_time < 5)
		think_time = 0;
	return think_time;
}
