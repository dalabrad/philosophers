/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:05:20 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/04 11:09:24 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

/*
* 1) Parse from argv => check input errors and fill the data table.
*	parse_input(&table, argv);
* 2) Create the mutex (forks), allocate data for forks, philo arrays...
*	data_init(&table);
* 3) Start the simulation
*	feast_start(&table);
* 4) Free all the allocated data (NO LEAKS!!!)
	clean(&table);
*/
int	main(int argc, char **argv)
{
	t_data	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argv) != 0)
			return (EXIT_FAILURE);
		if (data_init(&table) != 0)
			return (EXIT_FAILURE);
		feast_simulation(&table);
		clean(&table);
	}
	else
		return (error_msg(INPUT_ERROR));
	return (EXIT_SUCCESS);
}
