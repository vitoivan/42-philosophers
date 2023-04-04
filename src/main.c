/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:29:24 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/04 10:49:13 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		print_usage_message();
		return (1);
	}
	printf("argc: %d\n", argc);
	while (*argv)
		printf("argv: %s\n", *argv++);
	return (0);
}
