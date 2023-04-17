/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:10:01 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/17 09:40:24 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_actions
{
	FORK = 1,
	EAT,
	SLEEP,
	THINK,
	DIED
}					t_e_actions;

struct	s_ctx;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_count;
	pthread_t		*thread;
	int				last_eat;
	struct s_ctx	*ctx;
}					t_philo;

typedef struct s_ctx
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_count;
	int				must_eat_count;
	t_philo			**philos;
	pthread_mutex_t	**forks;
	pthread_mutex_t	someone_died_mutex;
	pthread_mutex_t	print_mutex;
	int				someone_died_flag;
	int				start_time;
}					t_ctx;

typedef struct s_worker_params
{
	t_ctx			*ctx;
	int				index;
}					t_worker_params;

int					validate_args(int argc, char **argv);
int					ft_isdigit(int ch);
int					ft_atoi(const char *nptr);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
t_ctx				*init_ctx(int argc, char **args);
void				free_ctx(t_ctx *ctx);
int					get_time(void);
int					get_forks(t_philo *philo);
int					fold_forks(t_philo *philo);
int					print_action(t_philo *philo, t_e_actions action);
int					eat(t_philo *philo);

#endif