/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:10:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/04 11:48:13 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
 * THis function checks the string and returns a pointer to the start of the
 * numeric characters of the string if:
 * 	1) There's no minus sign (-) ==> input values must be positive!!!
 * 	2) Valid numerical string:
 * 		"	   +769characters_&%" 	(OK)
 * 		" 	+char%/42"				 (X)
 * 	3) First Check of INT_MAX ==> len(numerical_str) > 10 (X)
 * 
 */
static const char	*valid_input(const char *str)
{
	const char	*nbr_ptr;

	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		error_msg(ARG_NEG);
		return (NULL);
	}
	if (!is_digit(*str))
	{
		error_msg(UNVALID_ARG);
		return (NULL);
	}
	nbr_ptr = str;
	return (nbr_ptr);
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = valid_input(str);
	if (!str)
		return (-1);
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > INT_MAX)
	{
		error_msg(ARG_TOO_BIG);
		result = -1;
	}
	return (result);
}

/* 	
 * 	INPUT DATA 
 *	=======================
 *            -----ms----
 *	./philo 5 600 300 200 [6] , [Optional]
 * I neeed to:
 * 		~ convert ms to μs (* 1e3) for timestamps.
 * 		~ Check if timestamps are greater that 60ms (6e4 μs).
*/
int	parse_input(t_data *table, char **argv)
{
	table->n_philo = (long)ft_atol(argv[1]);
	if (table->n_philo == -1)
		return (EXIT_FAILURE);
	if (table->n_philo == 0)
		return (error_msg(NO_PHILO_ERROR));
	table->time_die = (long)ft_atol(argv[2]) * 1e3;
	table->time_eat = (long)ft_atol(argv[3]) * 1e3;
	table->time_sleep = (long)ft_atol(argv[4]) * 1e3;
	if (table->time_die == -1e3 || table->time_eat == -1e3
		|| table->time_sleep == -1e3)
		return (EXIT_FAILURE);
	else if (table->time_die < 6e4 || table->time_eat < 6e4
		|| table->time_sleep < 6e4)
		return (error_msg(ARG_TOO_SMALL));
	if (argv[5])
	{
		table->n_limit_meals = ft_atol(argv[5]);
		if (table->n_limit_meals == -1)
			return (EXIT_FAILURE);
	}
	else
		table->n_limit_meals = -1;
	return (EXIT_SUCCESS);
}
