/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:00:13 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/18 22:40:16 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	init_philo(t_ctx **ctx, int i)
{
	(*ctx)->philos[i] = (t_philo *)malloc(sizeof(t_philo));
	(*ctx)->philos[i]->id = i + 1;
	(*ctx)->philos[i]->eat_count = 0;
	(*ctx)->philos[i]->last_eat = -1;
	(*ctx)->philos[i]->left_fork = (*ctx)->forks[i];
	(*ctx)->philos[i]->right_fork = (*ctx)->forks[(i + 1)
		% (*ctx)->philo_count];
	(*ctx)->philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
	(*ctx)->philos[i]->ctx = *ctx;
	(*ctx)->philos[i]->eating_flag = 0;
	(*ctx)->philos[i]->eating_mutex = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t));
	pthread_mutex_init((*ctx)->philos[i]->eating_mutex, NULL);
	pthread_mutex_init(&(*ctx)->philos[i]->last_eat_mutex, NULL);
}

static void	init_philos(t_ctx **ctx)
{
	int	i;

	i = 0;
	(*ctx)->philos = (t_philo **)malloc(sizeof(t_philo *)
			* (*ctx)->philo_count);
	while (i < (*ctx)->philo_count)
	{
		init_philo(ctx, i);
		i++;
	}
}

static void	init_forks(t_ctx **ctx)
{
	int	i;

	i = 0;
	(*ctx)->forks = malloc(sizeof(pthread_mutex_t *) * (*ctx)->philo_count);
	while (i < (*ctx)->philo_count)
	{
		(*ctx)->forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((*ctx)->forks[i], NULL);
		i++;
	}
}

t_ctx	*init_ctx(int argc, char **args)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->philo_count = ft_atoi(args[1]);
	ctx->time_to_die = ft_atoi(args[2]);
	ctx->time_to_eat = ft_atoi(args[3]);
	ctx->time_to_sleep = ft_atoi(args[4]);
	ctx->someone_died_flag = 0;
	ctx->full_philos = 0;
	ctx->start_time = get_time();
	if (argc == 6)
		ctx->must_eat_count = ft_atoi(args[5]);
	else
		ctx->must_eat_count = -1;
	ctx->monitor_threads = (pthread_t *)malloc(
			sizeof(pthread_t) * ctx->philo_count);
	pthread_mutex_init(&ctx->someone_died_mutex, NULL);
	pthread_mutex_init(&ctx->print_mutex, NULL);
	pthread_mutex_init(&ctx->full_philos_mutex, NULL);
	init_forks(&ctx);
	init_philos(&ctx);
	return (ctx);
}

void	free_ctx(t_ctx *ctx)
{
	int	i;

	if (!ctx)
		return ;
	i = 0;
	while (i < ctx->philo_count)
	{
		free(ctx->philos[i]->thread);
		pthread_mutex_destroy(ctx->forks[i]);
		free(ctx->forks[i]);
		pthread_mutex_destroy(ctx->philos[i]->eating_mutex);
		free(ctx->philos[i]->eating_mutex);
		free(ctx->philos[i]);
		i++;
	}
	free(ctx->philos);
	free(ctx->monitor_threads);
	free(ctx->forks);
	pthread_mutex_destroy(&ctx->someone_died_mutex);
	pthread_mutex_destroy(&ctx->print_mutex);
	pthread_mutex_destroy(&ctx->full_philos_mutex);
	ctx->philos = NULL;
	free(ctx);
}
