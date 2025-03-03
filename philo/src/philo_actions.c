/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:40:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/03 18:42:22 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * Eating action:
 * 	1) Grab the forks (lock).
 * 	2) Eat : update last meal time and meal counter. And bool philo->full
 * 		if reached n_limit_meals.
 * 	3) Release the forks (unlock).
*/
void	philo_eat(t_philo *philo)
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
 * Sleeping action:
 * 	1) Print the status.
 * 	2) Sleep for time_sleep.
*/
void	philo_sleep(t_philo *philo)
{
	write_status(SLEEPING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_sleep, philo->data);
}

/*
 * Thinking action: 
 * even philos have a set time to think and system is symetric.
 * odd philos is when we have to make the system fair.
 * 	1) Print the status if we are in simulation.
 *		we use philo_think() for the desynchronization!!
 * 	2) If philos are odd, calculate the theoretical t_think.
 * 		t_think = t_eat - 2 * t_sleep.
 * 		~ If it is negative -> t_think = 0.
 * 		~ If it is positive -> sleep for t_think * 0.42.
*/
void	philo_think(t_philo *philo, bool before_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!before_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->data->n_philo % 2)
	{
		t_eat = philo->data->time_eat;
		t_sleep = philo->data->time_sleep;
		t_think = t_eat - 2 * t_sleep;
		if (t_think < 0)
			t_think = 0;
		precise_usleep(t_think * 0.42, philo->data);
	}
}
