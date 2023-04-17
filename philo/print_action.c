/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/17 09:39:10 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	lock_print_mutex(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->ctx->someone_died_mutex);
	pthread_mutex_lock(&(*philo)->ctx->print_mutex);
}

static void	unlock_print_mutex(t_philo **philo)
{
	pthread_mutex_unlock(&(*philo)->ctx->print_mutex);
	pthread_mutex_unlock(&(*philo)->ctx->someone_died_mutex);
}

static void	print(t_e_actions action)
{
	if (action == FORK)
		printf("has taken a fork\n");
	else if (action == EAT)
		printf("is eating\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == THINK)
		printf("is thinking\n");
}

int	print_action(t_philo *philo, t_e_actions action)
{
	int	now;

	now = get_time();
	lock_print_mutex(&philo);
	if (philo->ctx->someone_died_flag == 1)
	{
		unlock_print_mutex(&philo);
		return (1);
	}
	printf("%d %d ", now - philo->ctx->start_time, philo->id);
	if (now - philo->last_eat >= philo->ctx->time_to_die)
	{
		printf("died\n");
		philo->ctx->someone_died_flag = 1;
		unlock_print_mutex(&philo);
		return (1);
	}
	else
		print(action);
	unlock_print_mutex(&philo);
	return (0);
}
