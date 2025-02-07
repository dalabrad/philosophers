/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:05:20 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/07 15:22:25 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo	philo;

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
			philo.n_must_eat = (size_t)transform_argument(argv[5]);
		printf("Number of philosophers : %zu\n", philo.n_philo);
		printf("Time to die : %zu\n", philo.time_die);
		printf("Time to eat : %zu\n", philo.time_eat);
		printf("Time to sleep : %zu\n", philo.time_sleep);
		if (argc == 6)
			printf("N times philo must eat (opt) : %zu\n", philo.n_must_eat);
	}
	return (EXIT_SUCCESS);
}
