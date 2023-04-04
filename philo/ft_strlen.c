/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 20:18:56 by victor            #+#    #+#             */
/*   Updated: 2023/04/04 13:31:52 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

size_t	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	if (s == NULL)
		return (0);
	while (s[n])
		n++;
	return ((size_t)n);
}
