/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:10:01 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/21 20:05:10 by coder            ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	is_taken_mutex;
	int				ind;
	int				is_taken;
	int				owner;
}					t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*left_fork;
	int				is_full;
	t_fork			*right_fork;
	pthread_mutex_t	*eating_mutex;
	pthread_mutex_t	last_eat_mutex;
	int				eating_flag;
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
	t_fork			*forks;
	pthread_mutex_t	someone_died_mutex;
	pthread_mutex_t	print_mutex;
	int				someone_died_flag;
	int				start_time;
	pthread_t		*monitor_threads;
	pthread_mutex_t	full_philos_mutex;
	int				full_philos;
}					t_ctx;

typedef struct s_monitor_data
{
	t_ctx	*ctx;
	int		i;
}					t_monitor_data;

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
time_t				get_time(void);
int					get_forks(t_philo *philo);
int					fold_forks(t_philo *philo);
int					print_action(t_philo *philo, t_e_actions action);
int					eat(t_philo *philo);
void				set_eating_flag(t_philo *philo, int flag);
int					get_eating_flag(t_philo *philo);
void				*monitor(void *v_ctx);
int					get_full_philos(t_ctx *ctx);
void				increase_full_philos(t_ctx *ctx);
int					ft_sleep(time_t time);
int					validate_philo_worker(t_philo *philo);
int					get_last_eat(t_philo *philo);
void				set_last_eat(t_philo *philo);
int 				get_think_time(t_philo *philo);
#endif