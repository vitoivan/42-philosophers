/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:29:24 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/05 09:21:18 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long int	time_calculator(long int time)
{
	struct timeval	tv;
	long int		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms - time);
}

void	print_action(t_philo *philo, t_e_actions action, long int time)
{
	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(philo->someone_died_mutex);
	if (*philo->someone_died_flag == 1)
	{
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(philo->someone_died_mutex);
		return ;
	}
	printf("%ld %d ", time_calculator(time), philo->id);
	if (action == FORK)
		printf("has taken a fork\n");
	else if (action == EAT)
		printf("is eating\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == THINK)
		printf("is thinking\n");
	else if (action == DIED)
		printf("died\n");
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->someone_died_mutex);
}

static int	get_time(void)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	someone_died(t_philo *philo)
{
	pthread_mutex_lock(philo->someone_died_mutex);
	if (*(philo->someone_died_flag))
	{
		pthread_mutex_unlock(philo->someone_died_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->someone_died_mutex);
	return (0);
}

int	validate_if_philo_died(t_philo *philo)
{
	int	now;

	now = get_time();
	if (now - philo->last_eat > philo->time_to_die)
	{
		printf("philo %d died\n", philo->id);
		pthread_mutex_lock(philo->someone_died_mutex);
		*(philo->someone_died_flag) = 1;
		pthread_mutex_unlock(philo->someone_died_mutex);
		return (1);
	}
	return (0);
}

void	*philo_worker(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, FORK, get_time());
		print_action(philo, FORK, get_time());
		if (someone_died(philo) || validate_if_philo_died(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		print_action(philo, EAT, get_time());
		usleep(philo->time_to_eat * 1000);
		philo->last_eat = get_time();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (validate_if_philo_died(philo) || validate_if_philo_died(philo))
			break ;
		print_action(philo, SLEEP, get_time());
		usleep(philo->time_to_sleep * 1000);
		if (someone_died(philo) || validate_if_philo_died(philo))
			break ;
		print_action(philo, THINK, get_time());
		usleep(100);
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
		// printf("philo %d is created\n", ctx->philos[i]->id);
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
