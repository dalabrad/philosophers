/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:06:56 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/01 11:51:23 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean(t_data *table)
{
	t_philo	*philo;
	t_fork	*fork;
	long	i;

	i = 0;
	while (i < table->n_philo)
	{
		philo = table->philos + i;
		fork = table->forks + i;
		safe_mutex_handle(&(philo->philo_mutex), DESTROY);
		safe_mutex_handle(&(fork->fork), DESTROY);
		i++;
	}
	safe_mutex_handle(&(table->table_mutex), DESTROY);
	safe_mutex_handle(&(table->write_mutex), DESTROY);
	free(table->philos);
	free(table->forks);
}
