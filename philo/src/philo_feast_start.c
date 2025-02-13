/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_feast_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:11:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/13 20:40:18 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	one_philo(t_data *table)
{
	//TO DO!!!
}

void	*feast_simulation(void *data)
{
	t_philo	*philo_ptr;

	philo_ptr = (t_philo *)data;
	wait_all_threads();// TO DO!!!
	return (NULL);
}

/*
 * ./philo 5 60 100 400 [6]
 * 
 * 0) If limit meals (optional value) is [0] --> nothing to do : return.
 * 0.1) If only 1 philo call ad hoc function.
 * 1) Create all threads (all philosophers).
 * 2) Create a thread to monitor the deaths.
 * 3) Synchronize the beggining of the simulation:
 *      phread_create() -> philo starts running !!!
 *      but we want every1 starting simultaneously.abort
 * 4) Join everyone.
*/
void	feast_start(t_data *table)
{
	size_t	i;

	if (table->n_limit_meals == 0)
		return ;
	else if (table->n_philo == 1)
		one_philo(table);
	else
	{
		while (i < table->n_philo)
		{
			safe_thread_handle(&(table->philos[i].thread_id),
				feast_simulation, &(table->philos[i]), CREATE);
		}
	}
}
