/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_feast_simulation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:11:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/06 09:53:10 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * This function creates the philo threads.
 *	~ If only 1 philo : use one_philo() routine.
 *	~ Else : use philo_routine() for all philos.
*/
static long	create_philo_threads(t_data *table)
{
	long	i;

	if (table->n_philo == 1)
	{
		if (safe_thread_handle(&(table->philos[0].thread_id), one_philo,
				&table->philos[0], CREATE) != 0)
			return (0);
		return (1);
	}
	i = 0;
	while (i < table->n_philo)
	{
		if (safe_thread_handle(&(table->philos[i].thread_id),
				philo_routine, &(table->philos[i]), CREATE) != 0)
			return (i);
		i++;
	}
	return (i);
}

/*
 * This function joins the philo threads.
*/
static void	join_philo_threads(t_data *table, long nbr_philo_threads)
{
	long	i;

	i = 0;
	while (i < nbr_philo_threads)
	{
		safe_thread_handle(&(table->philos[i].thread_id), NULL, NULL, JOIN);
		i++;
	}
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
void	feast_simulation(t_data *table)
{
	long	nbr_philo_threads;
	int		status;

	if (table->n_limit_meals == 0)
		return ;
	else
		nbr_philo_threads = create_philo_threads(table);
	if (nbr_philo_threads == table->n_philo)
	{
		status = safe_thread_handle(&(table->monitor),
				monitor_feast, table, CREATE);
		if (status != 0)
			set_bool(&(table->table_mutex), &table->end_simulation, true);
		table->start_simulation = get_time(MILISECOND);
	}
	else
	{	
		set_bool(&(table->table_mutex), &table->end_simulation, true);
		status = -1;
	}	
	set_bool(&(table->table_mutex), &(table->all_threads_ready), true);
	join_philo_threads(table, nbr_philo_threads);
	set_bool(&(table->table_mutex), &table->end_simulation, true);
	if (status == 0)
		safe_thread_handle(&(table->monitor), NULL, NULL, JOIN);
}
