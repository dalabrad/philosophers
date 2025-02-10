/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:06:22 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/10 19:51:00 by dalabrad         ###   ########.fr       */
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

static void	input_error_msg(void)
{
	ft_putstr_fd("Wrong input: Please enter:\n", 2);
	ft_putstr_fd("\t'./philo number_of_philosophers ", 2);
	ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
	ft_putstr_fd("(number_of_times_philosopher_must_eat)'.\n", 2);
}

/*
 * This function prints an error msg on STDERR_FLENO given the err_id.
 * it returns the err_id too so it can be used inside a return() or exit().
 */
int	error_msg(int err_id, char *arg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err_id == INPUT_ERROR)
		input_error_msg();
	else if (err_id == ARG_NEG)
	{
		ft_putstr_fd("Negative argument: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(". Arguments must be Positive.\n", STDERR_FILENO);
	}
	else if (err_id == UNVALID_ARG)
	{
		ft_putstr_fd("Unvalid argument: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(". Enter a valid numeric (positive) argument.\n", 2);
	}
	else if (err_id == ARG_TOO_BIG)
	{
		ft_putstr_fd("Argument too big: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(". Value of argument bigger that MAX_INT.\n", 2);
	}
	else if (err_id == ARG_TOO_SMALL)
		ft_putstr_fd("value of time stamps must be greater than 60ms\n", 2);
	return (err_id);
}

void	error_exit(int err_id, char *arg)
{
	exit (error_msg(err_id, arg));
}
