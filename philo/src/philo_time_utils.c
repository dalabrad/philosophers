/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:26:02 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/27 18:10:05 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * This function is like gettimeofday() but returns the value in the magnitude 
 * of time_code. This can be:
 *		~ SECONDS.
 * 		~ MILISECONDS.
 * 		~ MICROSECONDS.
*/
long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_str_exit("gettimeofday() failed\n");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_str_exit("Wrong time_code used for gettimeofday() call.\n");
}

/*
 * This function is aprecise take on usleep().
 * I need table variable because if simulation is finished I dont want to sleep
 * 1) usleep() most of time, not CPU intensive.
 * 2) Refine las microsec with spinlock.
*/
void	precise_usleep(long usec, t_data *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			return ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}
