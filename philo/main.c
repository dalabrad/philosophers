/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:05:20 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/10 18:08:06 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

/* int	main(int argc, char *argv[])
{
	t_data	philo;

	if (argc < 5 || argc > 6)
	{
		error_msg(INPUT_ERROR, NULL);
		return (EXIT_FAILURE);
	}
	else
	{
		philo.n_philo = (size_t)transform_argument(argv[1]);
		philo.time_die = (size_t)transform_argument(argv[2]);
		philo.time_eat = (size_t)transform_argument(argv[3]);
		philo.time_sleep = (size_t)transform_argument(argv[4]);
		if (argc == 6)
			philo.n_limit_meals = (long)transform_argument(argv[5]);
		printf("Number of philosophers : %zu\n", philo.n_philo);
		printf("Time to die : %zu\n", philo.time_die);
		printf("Time to eat : %zu\n", philo.time_eat);
		printf("Time to sleep : %zu\n", philo.time_sleep);
		if (argc == 6)
			printf("N times philo must eat (opt) : %zu\n", philo.n_limit_meals);
	}
	return (EXIT_SUCCESS);
}
 */

int	main(int argc, char **argv)
{
	t_data	table;
	
	if (argc == 5 || argc == 6)
	{
		printf("Here the main program %s should start!!\n", argv[0]);
/* 		//1) Parse from argv => check input format error and fill the data table.
		parse_input(&table);
		//2) Create the threads(philosophers) / mutex (forks), get the time ...
		data_init(&table);
		//3) Start the simulation
		feast_start(&table);
		//4) Free all the allocated data (NO LEAKS!!!)
		clean(&table); */
	}
	else
		error_exit(INPUT_ERROR, NULL);
}
