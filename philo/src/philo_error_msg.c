/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:06:22 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/10 17:54:40 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

/*
 * This function prints an error msg on STDERR_FLENO given the err_id.
 * it returns the err_id too so it can be used inside a return() or exit().
 */
int	error_msg(int err_id, char *arg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err_id == INPUT_ERROR)
	{
		ft_putstr_fd("Please enter:\n\t'./philo number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("(number_of_times_philosopher_must_eat)'.\n", 2);
	}
	else if (err_id == ARG_ERROR)
	{
		ft_putstr_fd("Unvalid argument : ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (err_id);
}

void	error_exit(int err_id, char *arg)
{
	exit (error_msg(err_id, arg));
}