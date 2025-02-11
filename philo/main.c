/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:05:20 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/11 10:07:45 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	table;

	if (argc == 5 || argc == 6)
	{
		printf("Here the main program %s should start!!\n", argv[0]);
		//1) Parse from argv => check input errors and fill the data table.
		parse_input(&table, argv);
/* 		//2) Create the threads(philosophers) / mutex (forks)...
		data_init(&table);
		//3) Start the simulation
		feast_start(&table);
		//4) Free all the allocated data (NO LEAKS!!!)
		clean(&table); */
	}
	else
		error_exit(INPUT_ERROR);
	return (EXIT_SUCCESS);
}
