/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_feast_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:11:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/01 16:53:25 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * ./philo 5 60 100 400 [6]
 * 
 * 0) If limit meals (optional value) is [0] --> nothing to do : return.
 * 0.1) If only 1 philo call ad hoc function.
 * 1) Create all threads (all philosophers).
 * 2) Create a thread to monitor the deaths.
 * 3) Synchronize the beggining of the simulation:
 *      phread_create() -> philo starts running !!!
 *      but we want every1 starting simultaneously.
 * 4) Join everyone.
*/
void	feast_simulation(t_data *table)
{
	long	i;

	if (table->n_limit_meals == 0)
		return ;
	else if (table->n_philo == 1)
		safe_thread_handle(&(table->philos[0].thread_id), one_philo,
			&table->philos[0], CREATE);
	else
	{
		i = 0;
		while (i < table->n_philo)
		{
			safe_thread_handle(&(table->philos[i].thread_id),
				philo_routine, &(table->philos[i]), CREATE);
			i++;
		}
	}
	safe_thread_handle(&(table->monitor), monitor_feast, table, CREATE);
	table->start_simulation = get_time(MILISECOND);
	set_bool(&(table->table_mutex), &(table->all_threads_ready), true);
	i = 0;
	while (i < table->n_philo)
	{
		safe_thread_handle(&(table->philos[i].thread_id), NULL, NULL, JOIN);
		i++;
	}
	set_bool(&(table->table_mutex), &table->end_simulation, true);
}
