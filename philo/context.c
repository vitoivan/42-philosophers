/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:00:13 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/05 09:04:40 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	init_philos(t_ctx **ctx)
{
	int	i;

	i = 0;
	(*ctx)->philos = (t_philo **)malloc(sizeof(t_philo *)
			* (*ctx)->philo_count);
	while (i < (*ctx)->philo_count)
	{
		(*ctx)->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		(*ctx)->philos[i]->id = i + 1;
		(*ctx)->philos[i]->eat_count = 0;
		(*ctx)->philos[i]->left_fork = (*ctx)->forks[i];
		(*ctx)->philos[i]->right_fork = (*ctx)->forks[(i + 1)
			% (*ctx)->philo_count];
		if (i % 2)
		{
			(*ctx)->philos[i]->left_fork = (*ctx)->forks[(i + 1)
				% (*ctx)->philo_count];
			(*ctx)->philos[i]->right_fork = (*ctx)->forks[i];
		}
		(*ctx)->philos[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		(*ctx)->philos[i]->time_to_die = (*ctx)->time_to_die;
		(*ctx)->philos[i]->time_to_eat = (*ctx)->time_to_eat;
		(*ctx)->philos[i]->time_to_sleep = (*ctx)->time_to_sleep;
		(*ctx)->philos[i]->eat_count = 0;
		(*ctx)->philos[i]->someone_died_mutex = &(*ctx)->someone_died_mutex;
		(*ctx)->philos[i]->print_mutex = &(*ctx)->print_mutex;
		(*ctx)->philos[i]->someone_died_flag = &(*ctx)->someone_died_flag;
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
	if (argc == 6)
		ctx->must_eat_count = ft_atoi(args[5]);
	else
		ctx->must_eat_count = -1;
	pthread_mutex_init(&ctx->someone_died_mutex, NULL);
	pthread_mutex_init(&ctx->print_mutex, NULL);
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
		free(ctx->philos[i]);
		pthread_mutex_destroy(ctx->forks[i]);
		free(ctx->forks[i]);
		i++;
	}
	free(ctx->philos);
	free(ctx->forks);
	ctx->philos = NULL;
	free(ctx);
}
