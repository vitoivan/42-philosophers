/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:29:24 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/23 14:16:02 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + tv.tv_usec / 1000;
	return (time);
}

static int	should_run(t_philo *philo)
{
	if (philo->ctx->must_eat_count == -1)
		return (1);
	else if (philo->eat_count < philo->ctx->must_eat_count)
		return (1);
	pthread_mutex_lock(&philo->ctx->someone_died_mutex);
	philo->is_full = 1;
	pthread_mutex_unlock(&philo->ctx->someone_died_mutex);
	return (0);
}

void	*philo_worker(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	set_last_eat(philo);
	if (!validate_philo_worker(philo))
		return (NULL);
	while (1 && should_run(philo))
	{
		if (get_forks(philo))
			break ;
		else if (eat(philo))
			break ;
		fold_forks(philo);
		if (should_run(philo) == 0)
			break ;
		if (print_action(philo, SLEEP))
			break ;
		ft_sleep(philo->ctx->time_to_sleep);
		if (print_action(philo, THINK))
			break ;
		if (get_think_time(philo) > 0)
			usleep(get_think_time(philo) * 1000);
	}
	increase_full_philos(philo->ctx);
	return (NULL);
}

static void	create_threads(t_ctx *ctx, t_monitor_data *data)
{
	int	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		data[i].i = i;
		data[i].ctx = ctx;
		pthread_create(ctx->philos[i]->thread, NULL, philo_worker,
			(void *)ctx->philos[i]);
		pthread_create(&ctx->monitor_threads[i], NULL, monitor,
			(void *)&data[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_ctx			*ctx;
	int				i;
	t_monitor_data	*data;

	if (validate_args(argc, argv))
		return (1);
	ctx = init_ctx(argc, argv);
	data = malloc(sizeof(t_monitor_data) * ctx->philo_count);
	if (!ctx)
		return (1);
	create_threads(ctx, data);
	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_join(*ctx->philos[i]->thread, NULL);
		pthread_join(ctx->monitor_threads[i], NULL);
		i++;
	}
	free_ctx(ctx);
	free(data);
	return (0);
}
