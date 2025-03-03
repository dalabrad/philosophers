/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_write_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:14:34 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/03 17:05:55 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
	long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->data))
		printf(W "%ld" RST " %d has taken 1º fork.🍴🍴🍴\t\t\t"
			B "[fork id : %d]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->data))
		printf(W "%ld" RST " %d has taken 2º fork.🍴🍴🍴\t\t\t"
			B "[fork id : %d]\n" RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->data))
		printf(W "%ld" C " %d is eating.🍝🍝🍝\t\t\t" RST
			M "[meal counter : %ld]\n"RST, elapsed,
			philo->id, philo->meal_counter);
	else if (status == SLEEPING && !simulation_finished(philo->data))
		printf(W "%ld" G " %d is sleeping.😴😴😴\n" RST, elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->data))
		printf(W "%ld" Y " %d is thinking.🤔🤔🤔\n" RST, elapsed, philo->id);
	else if (status == DIED)
		printf(R "\t\t💀💀💀%ld %d died.💀💀💀\n" RST, elapsed, philo->id);
}

/*
 * Prints the message:
 * [time_ms] [philo_id] [action: died, pick a fork ...]
 * Thread safe thanks to the write_mutex.
*/
void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->data->start_simulation;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	safe_mutex_handle(&(philo->data->write_mutex), LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->data))
			printf(W "%ld" RST " %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->data))
			printf(W "%ld" C " %d is eating\n"RST, elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->data))
			printf(W "%ld" G " %d is sleeping\n" RST, elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->data))
			printf(W "%ld" Y " %d is thinking\n" RST, elapsed, philo->id);
		else if (status == DIED)
			printf(R "%ld %d died\n" RST, elapsed, philo->id);
	}
	safe_mutex_handle(&(philo->data->write_mutex), UNLOCK);
}
