/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_synchro_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:33:37 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/27 16:44:57 by dalabrad         ###   ########.fr       */
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
