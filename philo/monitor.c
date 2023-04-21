/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/21 20:07:46 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	get_full_philos(t_ctx *ctx)
{
	int	full_philos;

	pthread_mutex_lock(&ctx->full_philos_mutex);
	full_philos = ctx->full_philos;
	pthread_mutex_unlock(&ctx->full_philos_mutex);
	return (full_philos);
}

void	increase_full_philos(t_ctx *ctx)
{
	pthread_mutex_lock(&ctx->full_philos_mutex);
	ctx->full_philos++;
	pthread_mutex_unlock(&ctx->full_philos_mutex);
}

int	monitor_single_philo(t_ctx *ctx, int *i)
{
	t_philo	*philo;
	int		now;

	philo = ctx->philos[*i];
	now = get_time();
	pthread_mutex_lock(&ctx->print_mutex);
	pthread_mutex_lock(&ctx->someone_died_mutex);
	if (ctx->someone_died_flag == 1|| philo->is_full == 1)
	{
		pthread_mutex_unlock(&ctx->print_mutex);
		pthread_mutex_unlock(&ctx->someone_died_mutex);
		return (0);
	}
	if (now - get_last_eat(philo) > ctx->time_to_die && !get_eating_flag(philo))
	{
		printf("%d %d died\n", now - philo->ctx->start_time, philo->id);
		ctx->someone_died_flag = 1;
		pthread_mutex_unlock(&ctx->print_mutex);
		pthread_mutex_unlock(&ctx->someone_died_mutex);
		return (0);
	}
	pthread_mutex_unlock(&ctx->print_mutex);
	pthread_mutex_unlock(&ctx->someone_died_mutex);
	return (1);
}

int	validate_philo_worker(t_philo *philo)
{
	if (philo->ctx->philo_count == 1)
	{
		print_action(philo, FORK);
		return (0);
	}
	if (philo->id % 2 == 0)
		ft_sleep(2);
	set_last_eat(philo);
	return (1);
}

void	*monitor(void *v_monitor_data)
{
	t_ctx			*ctx;
	t_monitor_data	*data;
	int				i;

	data = (t_monitor_data *)v_monitor_data;
	ctx = data->ctx;
	i = data->i;
	while (1 && get_full_philos(ctx) < ctx->philo_count)
	{
		if (!monitor_single_philo(ctx, &i))
			break ;
		usleep(500);
	}
	return (NULL);
}
