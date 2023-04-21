/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/21 19:51:51 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int		get_fork_status(t_fork *fork)
{
	int	is_taken;
	
	pthread_mutex_lock(&fork->is_taken_mutex);
	is_taken = fork->is_taken;
	pthread_mutex_unlock(&fork->is_taken_mutex);
	return is_taken;
}

void	take_fork(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->is_taken_mutex);
	fork->is_taken = 1;
	fork->owner = philo->id;
	pthread_mutex_unlock(&fork->is_taken_mutex);
}

void	fold_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->is_taken_mutex);
	fork->is_taken = 0;
	fork->owner = 0;
	pthread_mutex_unlock(&fork->is_taken_mutex);
}

int	take_right_and_wait_left(t_philo *philo)
{
	take_fork(philo->right_fork, philo);
	if (print_action(philo, FORK))
	{
		fold_fork(philo->right_fork);
		return (1);
	}
	while (get_fork_status(philo->left_fork))
		usleep(500);
	take_fork(philo->left_fork, philo);
	if (print_action(philo, FORK))
	{
		fold_fork(philo->right_fork);
		fold_fork(philo->left_fork);
		return (1);
	}
	return (0);
}

int take_left_and_wait_right(t_philo *philo)
{
	take_fork(philo->left_fork, philo);
	if (print_action(philo, FORK))
	{
		fold_fork(philo->left_fork);
		return (1);
	}
	while (get_fork_status(philo->right_fork))
		usleep(100);
	take_fork(philo->right_fork, philo);
	if (print_action(philo, FORK))
	{
		fold_fork(philo->right_fork);
		fold_fork(philo->left_fork);
		return (1);
	}
	return (0);
}


int	get_forks(t_philo *philo)
{
	int	left_fork_was_taken;
	int	right_fork_was_taken;

	left_fork_was_taken = 1;
	right_fork_was_taken = 1;
	while(left_fork_was_taken || right_fork_was_taken)
	{
		left_fork_was_taken = get_fork_status(philo->left_fork);
		right_fork_was_taken = get_fork_status(philo->right_fork);
		usleep(100);
	}
	if (!left_fork_was_taken)
		return (take_left_and_wait_right(philo));
	else if (!right_fork_was_taken)
		return (take_right_and_wait_left(philo));
	return (0);
}

int	fold_forks(t_philo *philo)
{
	fold_fork(philo->right_fork);
	fold_fork(philo->left_fork);
	return (0);
}
