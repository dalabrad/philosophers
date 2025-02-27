/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getters_setters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:46:35 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/27 16:23:38 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * This function sets a boolean variable pointed by dest to value.
*/
void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
 * This function returns the value of boolean variable pointed by bool_ptr.
*/
bool	get_bool(t_mutex *mutex, bool *bool_ptr)
{
	bool	value;

	safe_mutex_handle(mutex, LOCK);
	value = *bool_ptr;
	safe_mutex_handle(mutex, UNLOCK);
	return (value);
}

/*
 * This function resturns the value of boolean table->end_simulation, which
 * determines if we achievend end of the simulation.
*/
bool	simulation_finished(t_data *table)
{
	return (get_bool(&(table->table_mutex), &(table->end_simulation)));
}

/*
 * This function sets a long variable pointed by dest to value.
*/
void	set_long(t_mutex *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
 * This function returns the value of long variable pointed by long_ptr.
*/
long	get_long(t_mutex *mutex, long *long_ptr)
{
	long	value;

	safe_mutex_handle(mutex, LOCK);
	value = *long_ptr;
	safe_mutex_handle(mutex, UNLOCK);
	return (value);
}
