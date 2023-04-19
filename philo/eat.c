/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/18 22:23:07 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	set_eating_flag(t_philo *philo, int flag)
{
	pthread_mutex_lock(philo->eating_mutex);
	philo->eating_flag = flag;
	pthread_mutex_unlock(philo->eating_mutex);
}

int	get_eating_flag(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(philo->eating_mutex);
	flag = philo->eating_flag;
	pthread_mutex_unlock(philo->eating_mutex);
	return (flag);
}

void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
}

int	get_last_eat(t_philo *philo)
{
	int	last_eat;

	pthread_mutex_lock(&philo->last_eat_mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (last_eat);
}

int	eat(t_philo *philo)
{
	set_eating_flag(philo, 1);
	if (print_action(philo, EAT))
	{
		set_eating_flag(philo, 0);
		fold_forks(philo);
		return (1);
	}
	else
	{
		set_last_eat(philo);
		ft_sleep(philo->ctx->time_to_eat);
		philo->eat_count++;
	}
	set_eating_flag(philo, 0);
	return (0);
}
