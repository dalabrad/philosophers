/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:39:02 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/01 16:58:10 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * One philo routine:
 * 	1) Fake to lock (grab) the fork.
 * 	2) Sleep until monitor busts the philo.
*/
void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		get_time(MILISECOND));
	increase_long(&(philo->data->table_mutex),
		&(philo->data->nbr_threads_running));
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->data))
		usleep(200);
	return (NULL);
}

/*
 * Philo routine:
 * 0) Wait all philos --> synchronized start!!
 * 1) Endless loop philo
 * 	1.1) Check if philo is full --> end loop.
 * 	1.2) Eat.
 * 	1.3) Sleep.
 * 	1.4) Think.
*/
void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		get_time(MILISECOND));
	increase_long(&(philo->data->table_mutex),
		&(philo->data->nbr_threads_running));
	while (!simulation_finished(philo->data))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			return (NULL);
		philo_eat(philo);
        philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

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
