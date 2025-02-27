/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_feast_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:11:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/27 18:00:23 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	one_philo(t_data *table)
{
	//TO DO!!!
}

/*
 * 0) Wait all philos --> synchronized start!!
 * 1) Endless loop philo
 * 	1.1) Check if philo is full --> end loop.
 * 	1.2) Eat.
 * 	1.3) Sleep.
 * 	1.4) Think.
*/
void	*feast_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	while(!simulation_finished(philo->data))
	{
		if (philo->full) // TODO THREAD SAFE?!?
			return (NULL);
		eat(philo); //TO DO
		sleep(philo); //TO DO ---> I need precise usleep()!!!
		think(philo); // TO DO
	}
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
 *      but we want every1 starting simultaneously.
 * 4) Join everyone.
*/
void	feast_start(t_data *table)
{
	long	i;

	if (table->n_limit_meals == 0)
		return ;
	else if (table->n_philo == 1)
		one_philo(table);
	else
	{
		i = 0;
		while (i < table->n_philo)
		{
			safe_thread_handle(&(table->philos[i].thread_id),
				feast_simulation, &(table->philos[i]), CREATE);
			i++;
		}
	}
	table->start_simulation = get_time(MILISECOND);
	set_bool(&(table->table_mutex), &(table->all_threads_ready), true);
	i = 0;
	while (i < table->n_philo)
	{
		safe_thread_handle(&(table->philos[i].thread_id), NULL, NULL, JOIN);
		i++;
	}
}
