/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:27:37 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/04 13:41:22 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	print_usage_message(void)
{
	printf("Error: Wrong number of arguments\n");
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

static void	print_error_message(char *error_message, int *has_error)
{
	printf("Error: %s\n", error_message);
	*has_error = 1;
}

static int	print_messages(int n_philo, int die_time, int eat_time,
		int sleep_time)
{
	int	has_error;

	has_error = 0;
	if (n_philo < 2)
		print_error_message("Number of philosophers must be greater than 1",
			&has_error);
	if (die_time < 60)
		print_error_message("Time to die must be greater than 60ms",
			&has_error);
	if (eat_time < 60)
		print_error_message("Time to eat must be greater than 60ms",
			&has_error);
	if (sleep_time < 60)
		print_error_message("Time to sleep must be greater than 60ms",
			&has_error);
	return (has_error);
}

int	validate_digits(int argc, char **argv)
{
	int		i;
	int		j;
	char	*str;
	size_t	len;

	i = 0;
	j = 0;
	while (i < argc)
	{
		str = argv[i];
		len = ft_strlen(str);
		while (str && (size_t)j < len)
		{
			if (!ft_isdigit(str[j]) && str[j] != '-' && str[j] != '+' \
					&& str[j] != ' ' && ft_strcmp(str, "0") != 0)
			{
				printf("Error: Arguments must be numbers\n");
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		print_usage_message();
		return (1);
	}
	if (validate_digits(argc, argv + 1))
		return (1);
	if (print_messages(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
			ft_atoi(argv[4])))
		return (1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 1)
		{
			printf("Error: Number of times each philosopher must eat \
must be greater than 0\n");
			return (1);
		}
	}
	return (0);
}
