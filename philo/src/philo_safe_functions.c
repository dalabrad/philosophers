/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:53:51 by dalabrad          #+#    #+#             */
/*   Updated: 2025/02/11 11:04:15 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
 * This function is a malloc with protection. If data allocation fails
 * exits the program with the error message of MALLOC_ERROR.
*/
void	*safe_malloc(size_t bytes)
{
	void	*rtrn;

	rtrn = malloc(bytes);
	if (!rtrn)
		error_exit(MALLOC_ERROR);
	return (rtrn);
}
