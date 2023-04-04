/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:14:02 by victor            #+#    #+#             */
/*   Updated: 2023/04/04 13:13:53 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static int	ft_iswhite(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	signal;

	signal = 1;
	result = 0;
	while ((ft_iswhite((int)*nptr)) && *nptr)
		nptr++;
	if (*nptr == '-')
	{
		signal = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit((int)*nptr))
	{
		result *= 10;
		result += ((*nptr - '0') * signal);
		nptr++;
	}
	return (result);
}
