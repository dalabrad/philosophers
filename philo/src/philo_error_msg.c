/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:06:22 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/11 10:30:35 by dalabrad         ###   ########.fr       */
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
int	error_msg(int err_id)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err_id == INPUT_ERROR)
		ft_putstr_fd("Wrong input: Please enter:\n\t'./philo  " \
			"number_of_philosophers  time_to_die  time_to_eat  time_to_sleep" \
			"  [number_of_times_philosopher_must_eat]'.\n", STDERR_FILENO);
	else if (err_id == ARG_NEG)
		ft_putstr_fd("Negative argument: Arguments must be Positive.\n",
			STDERR_FILENO);
	else if (err_id == UNVALID_ARG)
		ft_putstr_fd("Unvalid argument: Enter a valid numeric (positive)" \
			" argument.\n", STDERR_FILENO);
	else if (err_id == ARG_TOO_BIG)
		ft_putstr_fd("Argument too big: Value of argument bigger than" \
			" MAX_INT.\n", STDERR_FILENO);
	else if (err_id == ARG_TOO_SMALL)
		ft_putstr_fd("Time stamp value too low : Value of time stamps must " \
			"be greater than 60ms.\n", STDERR_FILENO);
	else if (err_id == NO_PHILO_ERROR)
		ft_putstr_fd("Number of philosophers must be at least 1.\n", 2);
	return (err_id);
}

void	error_exit(int err_id)
{
	exit (error_msg(err_id));
}
