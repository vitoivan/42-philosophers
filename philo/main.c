/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:29:24 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/17 09:42:18 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	get_time(void)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + tv.tv_usec / 1000;
	return (time);
}

void	*philo_worker(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	while (1 && philo->eat_count < philo->ctx->must_eat_count)
	{
		if (get_forks(philo))
			break ;
		else if (eat(philo))
			break ;
		fold_forks(philo);
		if (print_action(philo, SLEEP))
			break ;
		else
			usleep(philo->ctx->time_to_sleep * 1000);
		if (print_action(philo, THINK))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_ctx	*ctx;
	int		i;

	if (validate_args(argc, argv))
		return (1);
	ctx = init_ctx(argc, argv);
	if (!ctx)
		return (1);
	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_create(ctx->philos[i]->thread, NULL, philo_worker,
			(void *)ctx->philos[i]);
		i++;
	}
	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_join(*ctx->philos[i]->thread, NULL);
		i++;
	}
	free_ctx(ctx);
	return (0);
}
