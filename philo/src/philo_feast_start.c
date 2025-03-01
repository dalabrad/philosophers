/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_feast_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:11:55 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/01 11:58:07 by dalabrad         ###   ########.fr       */
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
 * Eat routine:
 * 	1) Grab the forks (lock).
 * 	2) Eat : update last meal time and meal counter. And bool philo->full
 * 		if reached n_limit_meals.
 * 	3) Release the forks (unlock).
*/
static void	eat(t_philo *philo)
{
	safe_mutex_handle(&(philo->first_fork->fork), LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&(philo->second_fork->fork), LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		get_time(MILISECOND));
	philo->meal_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_eat, philo->data);
	if (philo->data->n_limit_meals > 0
		&& philo->meal_counter == philo->data->n_limit_meals)
		set_bool(&(philo->philo_mutex), &(philo->full), true);
	safe_mutex_handle(&(philo->first_fork->fork), UNLOCK);
	safe_mutex_handle(&(philo->second_fork->fork), UNLOCK);
}

/*
 * Needs a better implementation !!!
*/
static void	think(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
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
	set_long(&(philo->philo_mutex), &(philo->last_meal_time),
		get_time(MILISECOND));
	increase_long(&(philo->data->table_mutex),
		&(philo->data->nbr_threads_running));
	while (!simulation_finished(philo->data))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			return (NULL);
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->data->time_sleep, philo->data);
		think(philo);
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
		safe_thread_handle(&(table->philos[0].thread_id), one_philo,
			&table->philos[0], CREATE);
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
