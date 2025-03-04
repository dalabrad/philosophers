/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:48:20 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/04 11:31:26 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/* 	
 *	This function assigns the forks to the right and left to each philo. There's
 *	a priority assignment depending of the philo->id is even or odd. It is 
 *	important to know:
 *		~ philo->id ---> [1, n_philo] is the number given to the philosopher.
 *		~ philo_position ---> [0, n_philo - 1] is the position of philo in array.
 *	- The philo with odd id will try to first catch the fork at his left, i.e.
 *	  forks[philo_position], and then the right one.
 *	- The even id philo will first try to cath the right fork 
 *	  (i.e. forks[(philo_position + 1) % n_philos]) the the left one.
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	n_philos;

	n_philos = philo->data->n_philo;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % n_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % n_philos];
		philo->second_fork = &forks[philo_position];
	}
}

/* 	
 *	This function initializes the data of each philo struct for each philosopher.
 *	Sets:
 *		~ philo->id to the position of philo in table->philos array + 1
 *		~ philo->meal_counter of each philo to zero.
 *		~ philo->full to false of every philosopher.
 *		~ sets the pointer to the data table to each philosopher.
 *		~ sets the pointers to the forks of each philo with assign_forks(). 
*/
static int	philos_init(t_data *table)
{
	long	i;
	t_philo	*philo_ptr;

	i = 0;
	while (i < table->n_philo)
	{
		philo_ptr = table->philos + i;
		philo_ptr->id = i + 1;
		philo_ptr->meal_counter = 0;
		philo_ptr->full = false;
		philo_ptr->data = table;
		if (safe_mutex_handle(&(philo_ptr->philo_mutex), INIT) != 0)
			return (EXIT_FAILURE);
		assign_forks(philo_ptr, table->forks, i);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	table_mutex_init(t_data	*table)
{
	long	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (safe_mutex_handle(&(table->forks[i].fork), INIT) != 0)
			return (EXIT_FAILURE);
		table->forks[i].fork_id = i;
		i++;
	}
	if (safe_mutex_handle(&(table->table_mutex), INIT) != 0)
		return (EXIT_FAILURE);
	if (safe_mutex_handle(&(table->write_mutex), INIT) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* 	
 *	This function initializes the data left on the main data table:
 *		~ sets table->end_simulation to false.
 *		~ Allocates the data for the philos and forks arrays.
 *		~ Initializes the mutex for each fork, and sets the fork_id
 *		~ Initializes the data for each philo struct. See philos_init()
 *			for more info. 
*/
int	data_init(t_data *table)
{
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->nbr_threads_running = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (error_msg(MALLOC_ERROR));
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->n_philo);
	if (!table->forks)
	{
		free(table->philos);
		return (error_msg(MALLOC_ERROR));
	}
	if (table_mutex_init(table) != 0)
	{
		free(table->philos);
		free(table->forks);
		return (EXIT_FAILURE);
	}
	if (philos_init(table) != 0)
	{
		free(table->philos);
		free(table->forks);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
