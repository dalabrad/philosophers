/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_synchro_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:33:37 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/01 11:46:17 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/* 	 
 *	Spinlock to synchronize the start of the simulation.
*/
void	wait_all_threads(t_data *table)
{
	while (!get_bool(&(table->table_mutex), &(table->all_threads_ready)))
		;
}

/* 	 
 *	Monitor busy waits until all threads are running.
*/
bool	all_threads_running(t_mutex *mutex, long *nbr_threads, long nbr_philos)
{
	bool	rtrn;

	rtrn = false;
	safe_mutex_handle(mutex, LOCK);
	if (*nbr_threads == nbr_philos)
		rtrn = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (rtrn);
}

/* 	 
 *	This function increases the value of a long pinted by dest 
 *	on a thread safe way. Useful for the monitor synchro.
*/
void	increase_long(t_mutex *mutex, long *dest)
{
	safe_mutex_handle(mutex, LOCK);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK);
}
