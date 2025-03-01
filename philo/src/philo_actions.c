/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:40:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/01 17:08:32 by dalabrad         ###   ########.fr       */
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
 * Thinking action: NEED A BETTER IMPLEMENTATION!!!
* 	1) Print the status.
*/
void	philo_think(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}
