/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:10:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/28 20:04:02 by dalabrad         ###   ########.fr       */
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
	int			len;
	const char	*nbr_ptr;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
		error_exit(ARG_NEG);
	if (!is_digit(*str))
		error_exit(UNVALID_ARG);
	nbr_ptr = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		error_exit(ARG_TOO_BIG);
	return (nbr_ptr);
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result > INT_MAX)
		error_exit(ARG_TOO_BIG);
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
void	parse_input(t_data *table, char **argv)
{
	table->n_philo = (long)ft_atol(argv[1]);
	if (table->n_philo == 0)
		error_exit(NO_PHILO_ERROR);
	table->time_die = (long)ft_atol(argv[2]) * 1e3;
	table->time_eat = (long)ft_atol(argv[3]) * 1e3;
	table->time_sleep = (long)ft_atol(argv[4]) * 1e3;
	if (table->time_die < 6e4 || table->time_eat < 6e4
		|| table->time_sleep < 6e4)
		error_exit(ARG_TOO_SMALL);
	if (argv[5])
		table->n_limit_meals = ft_atol(argv[5]);
	else
		table->n_limit_meals = -1;
}
