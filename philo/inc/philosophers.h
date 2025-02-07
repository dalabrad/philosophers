/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:10:56 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/07 16:29:51 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define INPUT_ERROR 1
# define ARG_ERROR 2

typedef struct s_philo
{
	size_t	n_philo;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	n_must_eat;
}	t_philo;

//	src/philo_error_msg.c
int		error_msg(int err_id, char *arg);

//  src/philo_transform_argument.c
int		transform_argument(char *str);

#endif