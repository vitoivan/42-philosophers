/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/21 18:51:46 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

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

int	take_left_and_wait_right(t_philo *philo)
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
