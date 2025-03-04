/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:06:22 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/04 15:55:12 by dalabrad         ###   ########.fr       */
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

static int	error_msg_2(int err_id)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (err_id == WRONG_OPCODE)
		ft_putstr_fd("Handle function received a wrong opcode.\n",
			STDERR_FILENO);
	return (err_id);
}

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
	else if (err_id == MALLOC_ERROR)
		ft_putstr_fd("Malloc: failed allocating data.\n", 2);
	else
		return (error_msg_2(err_id));
	return (err_id);
}

/*
 * This function prints an error msg on STDERR_FLENO given the str
 * and returns int EXIT_FAILURE.
 */
int	error_str(char	*str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
