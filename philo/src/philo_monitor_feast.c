/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_feast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:11:05 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/28 19:13:54 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * This function checks if a philo died:
 * 	1) Checks if philo full. If full can't die.
 * 	2) Compares elapsed time from last meal versus t_to_die
 * 		If it is bigger philo died
 * 		Else philo is alive.
*/
static bool	philo_died(t_philo	*philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&(philo->philo_mutex), &(philo->full)) == true)
		return (false);
	elapsed = get_time(MILISECOND) - get_long(&(philo->philo_mutex),
			&(philo->last_meal_time));
	t_to_die = philo->data->time_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

/*
 * Monitor routine:
 * 	1) wait until all philo threads are running.
 * 	2) Check for dead philos
 * 		When a philo dies:
 * 		~ Set the bool end_simulation to true.
 * 		~ Print the death.
*/
void	*monitor_feast(void *data)
{
	t_data	*table;
	int		i;

	table = (t_data *)data;
	while (!all_threads_running(&(table->table_mutex),
			&(table->nbr_threads_running), table->n_philo))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->n_philo && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&(table->table_mutex), &(table->end_simulation), true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
			i++;
		}
	}
	return (NULL);
}
