/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:10:01 by victor.simo       #+#    #+#             */
/*   Updated: 2023/04/04 13:32:25 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		validate_args(int argc, char **argv);
int		ft_isdigit(int ch);
int		ft_atoi(const char *nptr);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);

#endif