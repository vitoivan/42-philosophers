/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/18 17:15:49 by victor           ###   ########.fr       */
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
	pthread_mutex_lock(&ctx->someone_died_mutex);
	pthread_mutex_lock(&ctx->print_mutex);
	if (ctx->someone_died_flag == 1)
	{
		pthread_mutex_unlock(&ctx->someone_died_mutex);
		pthread_mutex_unlock(&ctx->print_mutex);
		return (0);
	}
	if (now - philo->last_eat > ctx->time_to_die && !get_eating_flag(philo))
	{
		printf("%d %d died\n", now - philo->ctx->start_time, philo->id);
		ctx->someone_died_flag = 1;
		pthread_mutex_unlock(&ctx->someone_died_mutex);
		pthread_mutex_unlock(&ctx->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&ctx->someone_died_mutex);
	pthread_mutex_unlock(&ctx->print_mutex);
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
	}
	return (NULL);
}
